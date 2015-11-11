#ifndef __COMMON_HEADER_H__
#define __COMMON_HEADER_H__

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

enum TrainMethod_t {
    TM_TRAINDIR,
    TM_YOURSELF,
    TM_TRAINIMAGES
};

enum SampleInfo_t {
    SI_UNDEF = 0,
    SI_EXBNZ = 1,
    SI_NOBNZ = 2
};

struct Image_t
{
    cv::Mat image;
    SampleInfo_t info;
};

#endif //__COMMON_HEADER_H__