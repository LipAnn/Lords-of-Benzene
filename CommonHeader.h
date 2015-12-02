#ifndef __COMMON_HEADER_H__
#define __COMMON_HEADER_H__

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

using namespace std;

enum SampleInfo_t
{
    SI_UNDEF = 0,
    SI_EXBNZ = 1,
    SI_NOBNZ = 2
};

const int ROWS=150;
const int COLS=150;

struct Image_t
{
    cv::Mat image;
    SampleInfo_t info;
};

#endif //__COMMON_HEADER_H__
