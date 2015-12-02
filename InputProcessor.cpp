#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>

#include "InputProcessor.h"
#include "CommonHeader.h"

void InputProcessor::LoadImages(vector<Image_t> loaded_pack)
{
    given_pack = loaded_pack;
}

vector<Image_t>& InputProcessor::GetImages()
{
  return given_pack;
}

vector <Image_t> InputProcessor::ProcessImages (vector <Image_t> loaded_pack)
{
    LoadImages (loaded_pack);
    FilterImages ();
    //... Here we can insert some more methods
    return GetImages (loaded_pack);
}

void InputProcessor::FilterImages()
{
  for (long long i = 0; i < given_pack.size(); ++i)
    {
      cv::fastNlMeansDenoisingColored(given_pack[i].image, given_pack[i].image);
    }
}
