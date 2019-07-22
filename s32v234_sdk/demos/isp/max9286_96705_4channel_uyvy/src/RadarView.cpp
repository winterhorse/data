#include <cstdio>
#include <cmath>
#include <stdexcept>
#include <ogl/OGLWin.h>

#include "RadarView.hpp"

#include "nanovg.h"

int RadarView::numSignals = 16;

RadarView::RadarView(std::shared_ptr<NVGcontext> vgCtx, std::shared_ptr<CalibLUT> lut, const char* configPath)
	: vgCtx(vgCtx), lut(lut)
{
	loadConfig(configPath);

	const auto& rect = lut->header.car_Icon_Rect;
	frontCX = rect.x + rect.width / 2;
	frontCY = rect.y + cyOffset;
	rearCX = frontCX;
	rearCY = rect.br().y - cyOffset;

	// 车框在车头车尾处外接弧的半径
	innerR = std::sqrt((rect.width / 2) * (rect.width / 2) + (cyOffset * cyOffset));

	arcWidth = 20;
}

void RadarView::loadConfig(const char* configPath)
{
	FILE* fp = fopen(configPath, "r");
	if (fp == nullptr)
	{
		throw std::runtime_error(std::string("couldn't open ") + configPath);
	}
	fscanf(fp, "FrontRadius: %f\n", &frontR);
	fscanf(fp, "RearRadius: %f\n", &rearR);
	fscanf(fp, "LeftRightRadius: %f\n", &lrR);
	fscanf(fp, "CyOffset: %f\n", &cyOffset);
	fscanf(fp, "ArcWidth: %f\n", &arcWidth);
	fscanf(fp, "BorderColor: [%f, %f, %f, %f]\n",
		&borderColor.r,
		&borderColor.g,
		&borderColor.b,
		&borderColor.a);

	fscanf(fp, "NearColor: [%f, %f, %f, %f]\n",
		&nearColor.r,
		&nearColor.g,
		&nearColor.b,
		&nearColor.a);

	fscanf(fp, "FarColor: [%f, %f, %f, %f]\n",
		&farColor.r,
		&farColor.g,
		&farColor.b,
		&farColor.a);

	fclose(fp);
}


void RadarView::drawSignalFrontRear(float d, float cx, float cy, float outerR, float innerR, float beginAngle, float endAngle)
{
	int N = std::round((outerR - innerR) / arcWidth); // 最多有几段弧

	d = std::min(d, outerR - innerR); // 距离超出框的范围，取框的最外层

	int i = d / arcWidth; // 计算当前距离是第几段弧

	float greenStep = 1.0 / N; // 计算绿色值，颜色从离车身近为红色，远为黄色

	auto vg = vgCtx.get();

	nvgBeginPath(vg);

	auto rgba = nvgRGBA(255, 0, 0, 95);
	rgba.g = greenStep * i;
	nvgStrokeColor(vg, rgba);
	nvgStrokeWidth(vg, arcWidth);

	float r = i * arcWidth + innerR;
	nvgArc(vg, cx, cy, r, beginAngle, endAngle, NVG_CW);

	nvgStroke(vg);
}

void RadarView::drawSignalLeftRight(int dir, float d, float startX, float startY, float endX, float endY)
{
	float midHeight = rearCY - frontCY; // 雷达信号图中间部分的长度
	float midWidth = lrR - innerR; // 雷达信号图中间部分的宽度

	d = std::min(d, midWidth); // 超出当边界算

	int N = std::round(midWidth / arcWidth);
	float greenStep = 1.0 / N;

	int i = d / arcWidth; // 当前距离是第几条距离线

	auto vg = vgCtx.get();

	nvgBeginPath(vg);
	nvgMoveTo(vg, startX + dir * (innerR + i * arcWidth), startY);
	nvgLineTo(vg, endX + dir * (innerR + i * arcWidth), endY);

	auto rgba = nvgRGBA(255, 0, 0, 95);
	rgba.g = greenStep * i;

	// 画直线而非矩形，画矩形还要算坐标跟前后弧线对齐，太麻烦
	nvgStrokeColor(vg, rgba);
	nvgStrokeWidth(vg, arcWidth);
	nvgStroke(vg);
}

void RadarView::drawBorder()
{
	auto vg = vgCtx.get();

	nvgBeginPath(vg);
	nvgMoveTo(vg, frontCX - lrR, frontCY);
	nvgArc(vg, frontCX, frontCY, lrR, NVG_PI, NVG_PI / 3.0 * 4.0, NVG_CW);
	nvgArc(vg, frontCX, frontCY, frontR, NVG_PI / 3.0 * 4.0, NVG_PI / 3.0 * 5.0, NVG_CW);
	nvgArc(vg, frontCX, frontCY, lrR, NVG_PI / 3.0 * 5.0, NVG_PI / 3.0 * 6.0, NVG_CW);


	nvgLineTo(vg, rearCX + lrR, rearCY);
	nvgArc(vg, rearCX, rearCY, lrR, 0, NVG_PI / 3.0, NVG_CW);
	nvgArc(vg, rearCX, rearCY, rearR, NVG_PI / 3.0, NVG_PI / 3.0 * 2.0, NVG_CW);
	nvgArc(vg, rearCX, rearCY, lrR, NVG_PI / 3.0 * 2.0, NVG_PI, NVG_CW);

	nvgLineTo(vg, frontCX - lrR, frontCY);

	nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
	nvgStrokeWidth(vg, 1);
	nvgStroke(vg);
}


void RadarView::drawFullScreen(const float* signals)
{
	float winWidth = getScreenWidth();
	float winHeight = getScreenHeight();
	float bevWidth = lut->header.bev_img_width;
	float bevHeight = lut->header.bev_img_height;

	auto vg = vgCtx.get();

	nvgSave(vg);

	nvgTranslate(vg, winWidth, 0);
	nvgRotate(vg, NVG_PI / 2);
	nvgScale(vg, 1.0 * winHeight / bevWidth, 1.0 * winWidth / bevHeight);

	draw(signals);

	nvgRestore(vg);
}

void RadarView::draw(const float* signals)
{
	drawBorder();

	float params[][7] = {
		// front
		{0, frontCX, frontCY, lrR, innerR, NVG_PI, NVG_PI / 6.0 * 7.0},
		{0, frontCX, frontCY, lrR, innerR, NVG_PI / 6.0 * 7.0,  NVG_PI / 6.0 * 8.0},
		{0, frontCX, frontCY, frontR, innerR, NVG_PI / 6.0 * 8.0,  NVG_PI / 6.0 * 9.0},
		{0, frontCX, frontCY, frontR, innerR, NVG_PI / 6.0 * 9.0,  NVG_PI / 6.0 * 10.0},
		{0, frontCX, frontCY, lrR, innerR, NVG_PI / 6.0 * 10.0, NVG_PI / 6.0 * 11.0},
		{0, frontCX, frontCY, lrR, innerR, NVG_PI / 6.0 * 11.0, NVG_PI / 6.0 * 12.0},

		// rear
		{0, rearCX,  rearCY, lrR, innerR, 0,      NVG_PI / 6.0},
		{0, rearCX,  rearCY, lrR, innerR, NVG_PI / 6.0,        NVG_PI / 6.0 * 2.0},
		{0, rearCX,  rearCY, rearR, innerR, NVG_PI / 6.0 * 2.0,  NVG_PI / 6.0 * 3.0},
		{0, rearCX,  rearCY, rearR, innerR, NVG_PI / 6.0 * 3.0,  NVG_PI / 6.0 * 4.0},
		{0, rearCX,  rearCY, lrR, innerR, NVG_PI / 6.0 * 4.0,  NVG_PI / 6.0 * 5.0},
		{0, rearCX,  rearCY, lrR, innerR, NVG_PI / 6.0 * 5.0,  NVG_PI / 6.0 * 6.0}
	};

	for (int i = 0; i < 12; ++i)
	{
		if (signals[i] > 0)
		{
			drawSignalFrontRear(
				signals[i],
				params[i][1],
				params[i][2],
				params[i][3],
				params[i][4],
				params[i][5],
				params[i][6]
				);
		}
	}


	float midHeight = rearCY - frontCY;
	float lrParams[][4] = {
		{frontCX , frontCY, frontCX, frontCY + midHeight / 2},
		{frontCX, frontCY, frontCX, frontCY + midHeight / 2},

		{frontCX, frontCY + midHeight / 2, frontCX, frontCY + midHeight},
		{frontCX, frontCY + midHeight / 2, frontCX, frontCY + midHeight},
	};

	for (int i = 12; i < numSignals; ++i)
	{
		if (signals[i] > 0)
		{
			int dir = (i == 13 || i == 14) ? 1 : -1;
			int paramIdx = i - 12;
			drawSignalLeftRight(dir, signals[i], lrParams[paramIdx][0], lrParams[paramIdx][1], lrParams[paramIdx][2], lrParams[paramIdx][3]);
		}
	}
}



void RadarView::testFullScreen()
{
	float winWidth = getScreenWidth();
	float winHeight = getScreenHeight();
	float bevWidth = lut->header.bev_img_width;
	float bevHeight = lut->header.bev_img_height;

	auto vg = vgCtx.get();

	nvgTranslate(vg, winWidth, 0);
	nvgRotate(vg, NVG_PI / 2);
	nvgScale(vg, 1.0 * winHeight / bevWidth, 1.0 * winWidth / bevHeight);

	test();

	nvgRestore(vg);
}

void RadarView::test()
{
	drawBorder();

	float params[][7] = {
		// front
		{0, frontCX, frontCY, lrR, innerR, NVG_PI, NVG_PI / 6.0 * 7.0},
		{0, frontCX, frontCY, lrR, innerR, NVG_PI / 6.0 * 7.0,  NVG_PI / 6.0 * 8.0},
		{0, frontCX, frontCY, frontR, innerR, NVG_PI / 6.0 * 8.0,  NVG_PI / 6.0 * 9.0},
		{0, frontCX, frontCY, frontR, innerR, NVG_PI / 6.0 * 9.0,  NVG_PI / 6.0 * 10.0},
		{0, frontCX, frontCY, lrR, innerR, NVG_PI / 6.0 * 10.0, NVG_PI / 6.0 * 11.0},
		{0, frontCX, frontCY, lrR, innerR, NVG_PI / 6.0 * 11.0, NVG_PI / 6.0 * 12.0},

		// rear
		{0, rearCX,  rearCY, lrR, innerR, 0,      NVG_PI / 6.0},
		{0, rearCX,  rearCY, lrR, innerR, NVG_PI / 6.0,        NVG_PI / 6.0 * 2.0},
		{0, rearCX,  rearCY, rearR, innerR, NVG_PI / 6.0 * 2.0,  NVG_PI / 6.0 * 3.0},
		{0, rearCX,  rearCY, rearR, innerR, NVG_PI / 6.0 * 3.0,  NVG_PI / 6.0 * 4.0},
		{0, rearCX,  rearCY, lrR, innerR, NVG_PI / 6.0 * 4.0,  NVG_PI / 6.0 * 5.0},
		{0, rearCX,  rearCY, lrR, innerR, NVG_PI / 6.0 * 5.0,  NVG_PI / 6.0 * 6.0}
	};


	for (int i = 0; i < 12; ++i)
	{
		int N = round((params[i][3] - params[i][4]) / arcWidth);
		for (int j = 0; j < N; ++j)
		{
			drawSignalFrontRear(
				j * arcWidth,
				params[i][1],
				params[i][2],
				params[i][3],
				params[i][4],
				params[i][5],
				params[i][6]
				);
		}
	}

	float midHeight = rearCY - frontCY;
	float midWidth = lrR - innerR;
	int N = round(midWidth / arcWidth);
	float lrParams[][4] = {
		{frontCX , frontCY, frontCX, frontCY + midHeight / 2},
		{frontCX, frontCY, frontCX, frontCY + midHeight / 2},

		{frontCX, frontCY + midHeight / 2, frontCX, frontCY + midHeight},
		{frontCX, frontCY + midHeight / 2, frontCX, frontCY + midHeight},
	};

	for (int i = 12; i < numSignals; ++i)
	{
		for (int j = 0; j < N; j++)
		{
			int dir = (i == 13 || i == 14) ? 1 : -1;
			int paramIdx = i - 12;
			drawSignalLeftRight(dir, j * arcWidth, lrParams[paramIdx][0], lrParams[paramIdx][1], lrParams[paramIdx][2], lrParams[paramIdx][3]);
		}
	}
}
