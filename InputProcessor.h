#ifndef __INPUT_PROCESSOR_H__
#define __INPUT_PROCESSOR_H__

#include <opencv2/opencv.hpp>
#include "ImagePack_t.h"

class InputProcessor
{
  private:
    ImagePack_t given_pack;

  public:
    InputProcessor(ImagePack_t);

    ImagePack_t GetImages();
    void FilterImages(); // can return smth else
};

#endif // __INPUT_PROCESSOR_H__
