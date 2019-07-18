#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <math.h>
#include "LUT.h"
#include <vector>
#include "LuminanceEqualize.hpp"
#include <numeric>

#include <chrono>


/**
 * 遍历求每一块融合区域的灰度值
 * @param images
 * @param sum1
 * @param sum2
 * @param rowstart
 * @param rowend
 * @param colstart
 * @param colend
 */
void iterationSumBGR(cv::Mat* images, double& sum1, double& sum2, const int rowstart,
                  const int rowend, const int colstart, const int colend, const int birdviewWidth , const CalibLUT& lut, int& mergePixelNum){

    sum1 = 0;
    sum2 = 0;
    mergePixelNum = 0;
    int pic1, pic2, x_pos, y_pos;

	const float bgr2y[] = {0.114, 0.587, 0.299};

    for (int i = rowstart; i < rowend; ++i)
        for (int j = colstart; j < colend; ++j) {

            int idx = i * birdviewWidth + j;

            if ((lut.table[idx].wt_fusion != 0) && (lut.table[idx].wt_fusion != 255)) {

                mergePixelNum++;
                // pic1是前视图或后视图, 所以对于左下角情况, pic1=1, pic2=3;
                pic1 = lut.table[idx].pic1;
                pic2 = lut.table[idx].pic2;

                x_pos = lut.table[idx].point_pos1.x;
                y_pos = lut.table[idx].point_pos1.y;

				auto p = images[pic1].at<cv::Vec3b>(y_pos, x_pos);

				for (int i = 0; i < 3; ++i)
				{
					sum1 += p[i] * bgr2y[i];
				}

                x_pos = lut.table[idx].point_pos2.x;
                y_pos = lut.table[idx].point_pos2.y;


				p = images[pic2].at<cv::Vec3b>(y_pos, x_pos);
				for (int i = 0; i < 3; ++i)
				{
					sum2 += p[i] * bgr2y[i];
				}
            }
        }
}

void iterationSumUYVY(cv::Mat* images, double& sum1, double& sum2, const int rowstart,
                  const int rowend, const int colstart, const int colend, const int birdviewWidth , const CalibLUT& lut, int& mergePixelNum){

    sum1 = 0;
    sum2 = 0;
    mergePixelNum = 0;
    int pic1, pic2, x_pos, y_pos;

	const float bgr2y[] = {0.114, 0.587, 0.299};

    for (int i = rowstart; i < rowend; ++i)
        for (int j = colstart; j < colend; ++j) {

            int idx = i * birdviewWidth + j;

            if ((lut.table[idx].wt_fusion != 0) && (lut.table[idx].wt_fusion != 255)) {

                mergePixelNum++;
                // pic1是前视图或后视图, 所以对于左下角情况, pic1=1, pic2=3;
                pic1 = lut.table[idx].pic1;
                pic2 = lut.table[idx].pic2;

                x_pos = lut.table[idx].point_pos1.x;
                y_pos = lut.table[idx].point_pos1.y;

				auto p = images[pic1].at<cv::Vec2b>(y_pos, x_pos);
				sum1 += p[1];

                x_pos = lut.table[idx].point_pos2.x;
                y_pos = lut.table[idx].point_pos2.y;


				p = images[pic2].at<cv::Vec2b>(y_pos, x_pos);
				sum2 += p[1];
            }
        }
}


template<class TPixel, class IterationSumFunc>
void calcExposureGain(cv::Mat* images, const CalibLUT& lut, float* gains, IterationSumFunc iterationSum)
{


    // 表示融合区域长宽
    int mergeHeight = lut.header.car_Icon_Rect.y;
    int mergeWidth = lut.header.car_Icon_Rect.x;

    // 表示原图长宽
    int srcWidth = lut.header.src_img_width;
    int srcHeight = lut.header.src_img_height;

    // 表示俯视图长宽
    int birdviewWidth = lut.header.bev_img_width;
    int birdviewHeight = lut.header.bev_img_height;

     //表示待拼接的图像数量
    const int num_images = 4;

    //N表示两幅图像间重叠部分的像素数量
    cv::Mat_<int> N(num_images, num_images);
    N.setTo(0);

//    (cv::Mat_<int>(num_images, num_images)
//            << 0, 0, 1229, 1219,
//               0, 0, 613, 288,
//               1229, 613, 0, 0,
//               1219, 288, 0, 0);     // TODO (蔚蓝数据集)

    //I表示两幅图像间重叠部分的第一个元素所代表的图像的强度
    cv::Mat_<double> I(num_images, num_images);
    I.setTo(0);

    // 计算I：
	auto t1 = std::chrono::high_resolution_clock::now();

    double sum1;
    double sum2;
    int mergePixelNum;
    iterationSum(images, sum1, sum2, mergeHeight - 90, mergeHeight - 40, mergeWidth - 50, mergeWidth, birdviewWidth, lut, mergePixelNum);
    N(0,2) = N(2,0) = mergePixelNum;
    I(0,2) = sum1 / N(0,2);
    I(2,0) = sum2 / N(2,0);

    iterationSum(images, sum1, sum2, mergeHeight - 90, mergeHeight - 40, birdviewWidth - mergeWidth, birdviewWidth - mergeWidth + 50, birdviewWidth, lut, mergePixelNum);
    N(0,3) = N(3,0) = mergePixelNum;
    I(0,3) = sum1 / N(0,3);
    I(3,0) = sum2 / N(3,0);

    iterationSum(images, sum1, sum2, birdviewHeight - mergeHeight + 10, birdviewHeight - mergeHeight + 60, mergeWidth - 50, mergeWidth, birdviewWidth, lut, mergePixelNum);
    N(1,2) = N(2,1) = mergePixelNum;
    I(1,2) = sum1 / N(1,2);
    I(2,1) = sum2 / N(2,1);

    iterationSum(images, sum1, sum2, birdviewHeight - mergeHeight + 10, birdviewHeight - mergeHeight + 60, birdviewWidth - mergeWidth, birdviewWidth - mergeWidth + 50, birdviewWidth, lut, mergePixelNum);
    N(1,3) = N(3,1) = mergePixelNum;
    I(1,3) = sum1 / N(1,3);
    I(3,1) = sum2 / N(3,1);


    double alpha = 0.01;    //表示σN的平方的倒数
    double beta = 100;    //表示σg的平方的倒数

    cv::Mat_<double> A(num_images, num_images); A.setTo(0);
    cv::Mat_<double> b(num_images, 1); b.setTo(0);

    for (int i = 0; i < num_images; ++i)
    {
        for (int j = 0; j < num_images; ++j)
        {
            b(i, 0) += beta * N(i, j);
            A(i, i) += beta * N(i, j);
            if (j == i) continue;
            A(i, i) += 2 * alpha * I(i, j) * I(i, j) * N(i, j);
            A(i, j) -= 2 * alpha * I(i, j) * I(j, i) * N(i, j);

        }
    }

    cv::Mat_<double> gains_;
    cv::solve(A, b, gains_);


	auto t2 = std::chrono::high_resolution_clock::now();
	auto timeUsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout<<" !!!! allExposureComposition solve time cost = "<< timeUsed <<" ms. "<<std::endl;

    std::cout << "!!!gains = " << gains_ << std::endl;

	for (int i = 0; i < 4; ++i)
	{
		gains[i] = gains_(i, 0);
	}
}


template<class TPixel>
inline void calcExposureGainBGR(cv::Mat* images, const CalibLUT& lut, float* gains)
{
	calcExposureGain<TPixel>(images, lut, gains, iterationSumBGR);
}

template<class TPixel>
inline void calcExposureGainUYVY(cv::Mat* images, const CalibLUT& lut, float* gains)
{
	calcExposureGain<TPixel>(images, lut, gains, iterationSumUYVY);
}
