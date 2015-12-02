#ifndef __NEURAL_DETECTOR_H__
#define __NEURAL_DETECTOR_H__

#include <opencv2/opencv.hpp>
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
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


class NeuralDetector
{
  private:
    const int MAX_ITER=10000;
    const int ROWS=180;
    const int COLS=320;
    const int HIDDEN_COUNT=25;
    const double EPSILON=1e-6;
    const double PARAM1=1e-2;
    const double PARAM2=1e-2;
    CvANN_MLP machineBrain;

  public:
    void DetectShape(InputProcessor);

    std::vector<std::vector<cv::Point> > GetContours();
    std::vector<cv::Vec2i> GetHierarchy();
};

#endif // __NEURAL_DETECTOR_H__
