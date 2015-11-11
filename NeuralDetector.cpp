#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <vector>

#include "InputProcessor.h"
#include "NeuralDetector.h"
#include "ImagePack_t.h"

void NeuralDetector::DetectShape(InputProcessor processed_images)
{
  ImagePack_t images = processed_images.GetImages();
  long long i = 0;
  for (ImagePack_t::iterator it = images.begin(); it != images.end(); ++it, ++i) {
    cv::findContours(*it, contorus[i], hierarchy[i], CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
  }
}

std::vector<std::vector<cv::Point> > NeuralDetector::GetControus()
{
  return contorus;
}

std::vector<cv::Vec4i> NeuralDetector::GetHierarchy()
{
  return hierarchy;
}
