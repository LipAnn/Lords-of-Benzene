#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Spokesman.h"

/**
 *
 *TODO:
 * 1. Insert Qt4 GUI
 *
 *
**/

void Spokesman::PrintInvitation()
{
    std::cout << "Welcome, User! Choose one of the options below:\n";
    std::cout << "1. Process several images\n";
    std::cout << "2. Process images in directory\n";
    std::cout << "3. Train our system on your samples\n";
    std::cout << "4. Test the work of our system on basic sets of examples\n";
    std::cout << "5. Quit\n";
}

UseMode_t Spokesman::InteractWithUser()
{

    PrintInvitation();
    char option = 0;

    while (std::cin >> option && !(option <= '5' && option >= '1')) {
        std::cout << "ERROR! Wrong option: " << option << " Maybe mistyped?\n";
        PrintInvitation();
    }
    option -= '1';
    switch (option) {
        case 0:
            return UM_INPUT_IMAGE;
            break;
        case 1:
            return UM_INPUT_DIR;
            break;
        case 2:
            return UM_TRAIN_ON_NEW;
            break;
        case 3:
            return UM_TEST_SAMPLES;
            break;
        case 4:
            std::cout << "What a pity that you have finally finished your work...\n";
            return UM_IM_QUIT;
            break;
    }
}

void Spokesman::Err(std::string error_text)
{
    std::cout << "Error occurred: " << error_text << "\n";
}

void Spokesman::Msg(std::string msg_text)
{
    std::cout << "Msg: " << msg_text << "\n";
}

bool Spokesman::ShowImages(std::vector<Image_t> what_to_show)
{
    for (int i = 0; i < what_to_show.size(); i++) {
        //Displaying images
    }
}

std::vector<Image_t> Spokesman::InputImages(UseMode_t given_mode)
{
    string path;
    std::cout << "Enter image path: \n";
    Image_t new_elem;

    std::vector<Image_t> samples_vec;
    std::cin >> path;
    std::cout << path << " AZAZA\n";
    new_elem.image = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
    new_elem.info = SI_UNDEF;
    samples_vec.push_back(new_elem);
    return samples_vec;
}

std::vector <Image_t> Spokesman::InputDir(UseMode_t given_mode)
{
    std::string path_to_dir;
    std::cout << "Enter path to dir: \n";
    std::cin >> path_to_dir;

    std::vector<Image_t> samples_vec;
    DIR* directory = opendir(path_to_dir.c_str());
    std::string path = "";
    struct dirent *dd = NULL;
    struct stat stb;

    Image_t new_elem;
    if (given_mode == UM_INPUT_DIR) {
        while ((dd = readdir(directory)) != NULL) {
            path = path_to_dir + '/' + dd->d_name;
            if ( (lstat (path.c_str(), &stb) != -1) && S_ISREG(stb.st_mode)) {
                std::cout << "AZAZA LALKI\n";
                new_elem.image = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
                new_elem.info = SI_UNDEF;
                samples_vec.push_back(new_elem);
            }
        }
    } else if (given_mode == UM_TRAIN_ON_NEW || given_mode == UM_TEST_SAMPLES) {
        path = path_to_dir + '/' + dd->d_name + ".dat";
        std::ifstream fin(path.c_str());
        if (!fin.is_open()) {
            samples_vec.clear();
            return samples_vec;
        }
        std::string impath;
        while(fin >> impath >> new_elem.info) {
            impath = path + '/' + impath;
            new_elem.image = cv::imread(impath, CV_LOAD_IMAGE_GRAYSCALE);
            samples_vec.push_back(new_elem);
        }
        fin.close();
        return samples_vec;
    }
}
