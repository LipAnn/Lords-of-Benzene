#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "InputProcessor.h"
#include "CommonHeader.h"

void InputProcessor::LoadImages(vector<Image_t> loaded_pack)
{
    given_pack = loaded_pack;
}

vector<Image_t>& InputProcessor::GetImages()
{
  return given_pack;
}

vector <Image_t> InputProcessor::ProcessImages (vector <Image_t> loaded_pack)
{
    LoadImages (loaded_pack);
    FilterImages ();
    ResizeImages ();
    //... Here we can insert some more methods
    return GetImages (loaded_pack);
}

void InputProcessor::FilterImages()
{
    cv::Mat edged_mask;
    int low_threshold = 100;
     for (long long i = 0; i < given_pack.size(); ++i) {
        //Transforming image to grayscale
        cv::cvtColor (given_pack[i].image, given_pack[i].image, CV_RGB2GRAY);
        /// Reduce noise with a kernel 3x3
        cv::blur(given_pack[i].image, edged_mask, cv::Size(3,3) );
        
        /// Canny detector
        Canny(edged_mask, edged_mask, low_threshold, low_threshold*3, 3);
        
        /// Using Canny's output as a mask, we display our result
        given_pack[i].image = cv::Scalar::all(0);
        
        given_pack[i].image.copyTo(given_pack[i].image, edged_mask);
    }
}

void InputProcessor::ResizeImages()
{
    for (long long i = 0; i < given_pack.size(); ++i) {
        cv::resize(given_pack[i].image, given_pack[i].image, cv::Size(ROWS, COLS), 0, 0, cv::INTER_LINEAR);
    }
}
