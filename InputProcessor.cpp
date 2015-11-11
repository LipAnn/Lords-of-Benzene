#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>

#include "InputProcessor.h"
#include "ImagePack_t.h"

InputProcessor::InputProcessor(ImagePack_t im_pack) : given_pack(im_pack) {}

ImagePack_t InputProcessor::GetImages()
{
  return given_pack;
}

void InputProcessor::FilterImages()
{
  for (ImagePack_t::iterator it = given_pack.begin(); it != given_pack.end(); ++it)
    {
      cv::fastNlMeansDenoisingColored(*it, *it);
    }
}
