#ifndef __INPUT_PROCESSOR_H__
#define __INPUT_PROCESSOR_H__

#include <opencv2/opencv.hpp>
#include <vector>
#include "CommonHeader.h"

class InputProcessor
{
  private:
    vector<Image_t> given_pack;

  public:
    InputProcessor(vector<Image_t>);

    vector<Image_t>& GetImages();
    void FilterImages(); // can return smth else
};

#endif // __INPUT_PROCESSOR_H__
