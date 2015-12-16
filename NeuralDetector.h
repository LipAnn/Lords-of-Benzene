#ifndef __NEURAL_DETECTOR_H__
#define __NEURAL_DETECTOR_H__

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "InputProcessor.h"
#include "CommonHeader.h"


class NeuralDetector
{
  public:

    CvANN_MLP machineBrain;
    NeuralDetector ();
    ~NeuralDetector() = default;
    std::vector<Image_t> DetectImages(std::vector<Image_t> images);
    bool Train(std::vector<Image_t> images);

  private:
    const int MAX_ITER=10000;
    const int HIDDEN_COUNT=25;
    const double MLP_EPSILON=1e-6;
    const double PARAM1=1e-2;
    const double PARAM2=1e-2;
    const double PREDICT_EPSILON=0.9;
};

#endif // __NEURAL_DETECTOR_H__
