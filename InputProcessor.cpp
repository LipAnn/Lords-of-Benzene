#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>

#include "InputProcessor.h"
#include "CommonHeader.h"

InputProcessor::InputProcessor(ImagePack_t im_pack) : given_pack(im_pack) {}

vector<Image_t>& InputProcessor::GetImages()
{
  return given_pack;
}

void InputProcessor::FilterImages()
{
  for (long long i = 0; i < given_pack.size(); ++i)
    {
      cv::fastNlMeansDenoisingColored(given_pack[i].image, given_pack[i].image);
    }
}
