#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <vector>

#include "InputProcessor.h"
#include "NeuralDetector.h"
#include "CommonHeader.h"

NeuralDetector::NeuralDetector()
{
    cv::Mat layers(4, 1, CV_32SC1);
    layers.row (0) = cv::Scalar(ROWS * COLS);
    layers.row (1) = cv::Scalar(HIDDEN_COUNT);
    layers.row (2) = cv::Scalar(HIDDEN_COUNT);
    layers.row (3) = cv::Scalar(1);
    machineBrain.create(layers, CvANN_MLP::SIGMOID_SYM, 1, 1);
}

vector<Image_t> NeuralDetector::DetectImages(vector<Image_t> images)
{
    size_t images_count = images.size();
    cv::Mat predictData(images_count, ROWS * COLS, CV_32FC1);
    cv::Mat predout(images_count, 1, CV_32FC1);

    for (size_t i = 0; i < images_count; ++i) {
        (images[i].image.reshape(0, 1)).copyTo(predictData.row(i));
    }

    machineBrain.predict(predictData, predout);

    for (size_t i = 0; i < images_count; ++i) {
        if (predout.at<float>(i, 0) >= PREDICT_EPSILON) {
            images[i].info = SI_EXBNZ;
        } else {
            images[i].info = SI_NOBNZ;
        }
    }
    return images;
}

bool NeuralDetector::Train(vector<Image_t> images)
{
    size_t images_count = images.size();
    cv::Mat trainData(images_count, ROWS * COLS, CV_32FC1);
    cv::Mat trainOutput(images_count, 1, CV_32FC1);

    for (size_t i = 0; i < images_count; ++i) {
        (images[i].image.reshape(0, 1)).copyTo(trainData.row(i));
        if (images[i].info == SI_UNDEF) {
            return false;
        }
        trainOutput.at<float>(i, 0) = (images[i].info == SI_EXBNZ ? 1 : -1);
    }
    machineBrain.train(
       trainData,
       trainOutput,
       cv::Mat(),
       cv::Mat(),
       CvANN_MLP_TrainParams(
           cvTermCriteria(
               CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,
               MAX_ITER,
               MLP_EPSILON
               ),
           CvANN_MLP_TrainParams::BACKPROP,
           PARAM1,
           PARAM2
           )
       );
    machineBrain.save("savednet.txt");
    std::cout << "Saved\n";
    return true;
}
