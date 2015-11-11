#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

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
}

bool ImagePack_t::DeleteImage(int index)
{
}

cv::Mat ImagePack_t::operator[](int index)
{
    return sample_pack[index];
}

int ImagePack_t::size()
{
    return sample_pack.size();
}
