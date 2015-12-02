#ifndef __INPUT_PROCESSOR_H__
#define __INPUT_PROCESSOR_H__

#include <opencv2/opencv.hpp>
#include <vector>
#include "CommonHeader.h"

class InputProcessor
{
  private:
    vector <Image_t> given_pack;
    
    void FilterImages(); // can return smth else

  public:
    vector <Image_t> ProcessImages (vector <Image_t> loaded_pack);
    void LoadImages (vector <Image_t> loaded_pack);
    vector <Image_t> GetImages();
};

#endif // __INPUT_PROCESSOR_H__
