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

class ImagePack_t
{
  public:
    vector<cv::Mat> sample_pack;
    vector<bool> sample_info;

    int size ();
    bool AddImage (cv::Mat image, bool image_info = false);
    bool DeleteImage (int index);
    cv::Mat operator[] (int index);
};

bool ImagePack_t::AddImage(cv::Mat image, bool image_info)
{
    sample_pack.insert(sample_pack.end(), image);
    sample_info.insert(sample_pack.end(), image_info);

    return 1;
}

bool ImagePack_t::DeleteImage(int index)
{
    sample_pack.erase (sample_pack.begin() + index);
    sample_info.erase (sample_info.begin() + index);

    return 1;
}

cv::Mat ImagePack_t::operator[](int index)
{
    return sample_pack[index];
}

int ImagePack_t::size()
{
    return sample_pack.size();
}

#endif //__COMMON_HEADER_H__