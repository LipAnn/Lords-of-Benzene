#ifndef __INPUT_PROCESSOR_H__
#define __INPUT_PROCESSOR_H__

#include <opencv2/opencv.hpp>
#include <vector>
#include "CommonHeader.h"

class InputProcessor
{

  private:
    std::vector<Image_t> given_pack;
    void FilterImages(); // can return smth else
    void ResizeImages();

  public:
    std::vector<Image_t> ProcessImages(std::vector <Image_t> loaded_pack);
    void LoadImages(std::vector <Image_t> loaded_pack);
    std::vector<Image_t> GetImages();
};

#endif // __INPUT_PROCESSOR_H__
