#ifndef __NEURAL_DETECTOR_H__
#define __NEURAL_DETECTOR_H__

#include <opencv2/opencv.hpp>
#include <vector>

#include "InputProcessor.h"


class NeuralDetector
{
  private:
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

  public:
    void DetectShape(InputProcessor);

    std::vector<std::vector<cv::Point> > GetContours();
    std::vector<cv::Vec2i> GetHierarchy();
};

#endif // __NEURAL_DETECTOR_H__
