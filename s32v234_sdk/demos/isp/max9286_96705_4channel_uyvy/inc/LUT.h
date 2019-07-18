#pragma once

#include <opencv2/core.hpp>
#include <cstdint>


namespace _panorama
{
enum Direction : uint8_t
{
	Front = 0,
	Back = 1,
	Left = 2,
	Right = 3
};

struct TacPoint
{
	int16_t x;
	int16_t y;
	uint8_t wt_upleft;
	uint8_t wt_upright;
	uint8_t wt_downleft;
	uint8_t wt_downright;
};


struct LUTPoint
{
	uint8_t pic1;		// front or rear
	uint8_t pic2;		// left or right
	uint8_t wt_fusion;	// weight of point1
	TacPoint point_pos1;
	TacPoint point_pos2;
};

struct LUTHeader
{
	uint32_t struct_version;

	cv::Rect carRealRect;
	cv::Rect car_Icon_Rect;

	uint32_t src_img_width;
	uint32_t src_img_height;
	uint32_t bev_img_width;
	uint32_t bev_img_height;
	int32_t cx, cy;
	float mm_per_pixel_w, mm_per_pixel_h;

	int32_t padding;
};

}

struct CalibLUT
{
	_panorama::LUTHeader header;
	_panorama::LUTPoint* table;

	CalibLUT(): table(nullptr) {}
	~CalibLUT()
	{
		if (table != nullptr)
		{
			delete[] table;
		}
	}

	bool load(const char* filename);
	bool save(const char* filename);
};
