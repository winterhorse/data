#pragma once

#include <memory>
#include <GLES2/gl2.h>

#include "LUT.h"
#include "nanovg.h"

class RadarView
{
public:
	RadarView() = default;
	RadarView(std::shared_ptr<NVGcontext> vgCtx, std::shared_ptr<CalibLUT> lut, const char* configPath);

	/**
	 * 画雷达图
	 * @param signals 16个雷达信号，每个信号的距离用像素计
	 */
	void draw(const float* signals);
	void drawFullScreen(const float* signals);

	void test();
	void testFullScreen();

	/*
	 * 画雷达信号图的框
	 */
	void drawBorder();

	/**
	 * 画车头和车尾测的雷达信号，画的都是弧线
	 * @param d 雷达信号的距离（用像素计），为了方便画线，d 其实并不真实等价于到车身的距离，
	 * 			而是到 innerR 这个外接弧线的距离
	 * @param cx 弧的圆心
	 * @param cy
	 * @param outerR 弧的最大半径，即离车身最远的雷达信号线的半径
	 * @param innerR 弧的最小半径，即离车身最远的雷达信号线的半径，也是车框在车头车尾处的外接弧的半径
	 * @param beginAngle 弧线起始角
	 * @param endAngle 弧线终止角
	 */
	void drawSignalFrontRear(float d, float cx, float cy, float outerR, float innerR, float beginAngle, float endAngle);


	void drawSignalLeftRight(int dir, float d, float startX, float startY, float endX, float endY);


private:

	void loadConfig(const char* configPath);

	static int numSignals;
	float frontCX, frontCY;
	float rearCX, rearCY;
	float lrR, frontR, rearR;
	float innerR;
	float arcWidth;

	float cyOffset;

	NVGcolor borderColor, nearColor, farColor;

	std::shared_ptr<NVGcontext> vgCtx;
	std::shared_ptr<CalibLUT> lut;
};
