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
#include <cmath>

enum //const!
{
    TRAIN_SAMPLE_COUNT=50,
    MAX_ITER=10000, //10000
    ROWS = 180, // / 6
    COLS = 320,
    HIDDEN_COUNT=25, //25
    PREDICT_SAMPLE_COUNT=31
};

const double MY_EPSILON=0.000001; //0.000001
const double PARAM1=0.1, PARAM2=0.1;


CvANN_MLP machineBrain;
cv::Mat trainImages[TRAIN_SAMPLE_COUNT];
cv::Mat predictImages[PREDICT_SAMPLE_COUNT];

cv::Mat trainOutput(TRAIN_SAMPLE_COUNT, 1, CV_32FC1);
cv::Mat predictOutput(TRAIN_SAMPLE_COUNT, 1, CV_32FC1);

cv::Mat trainData(TRAIN_SAMPLE_COUNT, ROWS * COLS, CV_32FC1);
cv::Mat predictData(PREDICT_SAMPLE_COUNT, ROWS * COLS, CV_32FC1);

void resizeImage(cv::Mat &image, int rows=ROWS, int cols=COLS)
{
    cv::resize(image, image, cv::Size(rows, cols), 0, 0, cv::INTER_LINEAR);
}


void getTrainData(std::string train_pict, std::string answers)
{
    std::ifstream fin1(train_pict.c_str());
    std::ifstream fin2(answers.c_str());
    std::string filename;
    int ans;
    cv::Mat image;
    for (int i = 0; i < TRAIN_SAMPLE_COUNT; ++i) {
        fin1 >> filename;
        fin2 >> ans;
        image = cv::imread("./train_images/" + filename, CV_LOAD_IMAGE_GRAYSCALE);
        resizeImage(image);
        image.copyTo(trainImages[i]);
        trainOutput.at<float>(i, 0) = ans;
        std::cout << trainOutput.at<float>(i, 0) << ' ' << filename << std::endl;
    }
    fin1.close();
    fin2.close();
}

void getPredictData(std::string pred_pict, std::string answers)
{
    std::ifstream fin1(pred_pict.c_str());
    std::ifstream fin2(answers.c_str());
    std::string filename;
    int ans;
    cv::Mat image;
    for (int i = 0; i < PREDICT_SAMPLE_COUNT; ++i) {
        fin1 >> filename;
        fin2 >> ans;
        image = cv::imread("./predict_images/" + filename, CV_LOAD_IMAGE_GRAYSCALE);
        resizeImage(image);
        image.copyTo(predictImages[i]);
        predictOutput.at<float>(i, 0) = ans;
        std::cout << predictOutput.at<float>(i, 0) << ' ' << filename << std::endl;
    }
    fin1.close();
    fin2.close();
}

void copyDataToMLPFormat(cv::Mat *from, cv::Mat &to, size_t data_size)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        (from[i].reshape(0, 1)).copyTo(to.row(i));
    }
}

void trainMachine()
{
    std::cout << "TRAIN BRAINS\n";

    copyDataToMLPFormat(trainImages, trainData, TRAIN_SAMPLE_COUNT);

    std::cout << "I'm here" << std::endl;

    machineBrain.train(
       trainData,
       trainOutput,
       cv::Mat(),
       cv::Mat(),
       CvANN_MLP_TrainParams(
           cvTermCriteria(
               CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,
               MAX_ITER,
               MY_EPSILON
               ),
           CvANN_MLP_TrainParams::BACKPROP,
           PARAM1,
           PARAM2
           )
       );
    std::cout << "Settings:\n";
    std::cout << "train sample count " << TRAIN_SAMPLE_COUNT;
    std::cout <<  " MaxIter " << MAX_ITER;
    std::cout << " Epsilon " << MY_EPSILON;
    std::cout << " Param1 " << PARAM1;
    std::cout << " Param2 " << PARAM2 << std::endl;
}

void createMachine()
{
    cv::Mat layers(4, 1, CV_32SC1);
    layers.row (0) = cv::Scalar(ROWS * COLS);
    layers.row (1) = cv::Scalar(HIDDEN_COUNT);
    layers.row (2) = cv::Scalar(HIDDEN_COUNT);
    layers.row (3) = cv::Scalar(1);
    machineBrain.create(layers, CvANN_MLP::SIGMOID_SYM, 1, 1);
}

cv::Mat predict(cv::Mat *images, int count_images=PREDICT_SAMPLE_COUNT, cv::Mat &to=predictData)
{
    copyDataToMLPFormat(images, to, count_images);
    cv::Mat predout(count_images, 1, CV_32FC1);
    machineBrain.predict(to, predout);
    for (int i = 0; i < count_images ; ++i) {
        predout.at<float>(i, 0) = (predout.at<float>(i, 0) + 1) / 2.0;
    }
    return predout;
}

cv::Mat checkBrain()
{
    return predict(trainImages, TRAIN_SAMPLE_COUNT, trainData);
}

double quality(cv::Mat &output, cv::Mat &ans, size_t cnt)
{
    double answer = 0.0;
    for (size_t i = 0; i < cnt; ++i) {
        if (ans.at<float>(i, 0) == 1) {
            answer -= log(std::max((double) output.at<float>(i, 0), MY_EPSILON));
        } else {
            answer -= log(std::max((double) 1 - output.at<float>(i, 0), MY_EPSILON));
        }
    }
    answer /= cnt;
    return answer;
}

int main(int argc, char **argv)
{
    getTrainData(argv[1], argv[2]); // argv[1] --- picture names, argv[2] --- answers names
    createMachine();
    trainMachine();
    machineBrain.save("savednet3.txt");
    std::cout << "Saved\n";
    cv::Mat train_predictions = checkBrain();
    std::cout << "TRAIN PREDICTIONS:\n";
    for (int i = 0; i < TRAIN_SAMPLE_COUNT; ++i) {
        std::cout << train_predictions.at<float>(i, 0) << ' ' << trainOutput.at<float>(i, 0) << std::endl;
    }
    std::cout << "TRAINING QUALITY:\n" << quality(train_predictions, trainOutput, TRAIN_SAMPLE_COUNT) << std::endl;
    getPredictData(argv[3], argv[4]);
    cv::Mat predictions = predict(predictImages);
    std::cout << "PREDICTIONS:\n";
    for (int i = 0; i < PREDICT_SAMPLE_COUNT; ++i) {
        std::cout << predictions.at<float>(i, 0) << ' ' << predictOutput.at<float>(i, 0) << std::endl;
    }
    std::cout << "PREDICTIONS QUALITY:\n" << quality(predictions, predictOutput, PREDICT_SAMPLE_COUNT) << std::endl;
    return 0;
}








