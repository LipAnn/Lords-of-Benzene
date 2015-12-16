#ifndef __SPOKESMAN_H__
#define __SPOKESMAN_H__

#include "CommonHeader.h"
#include <string.h>

enum UseMode_t {
    UM_INPUT_IMAGE,
    UM_INPUT_DIR,
    UM_TEST_SAMPLES,
    UM_TRAIN_ON_NEW,
    UM_IM_QUIT
};

class Spokesman
{
  public:
    UseMode_t InteractWithUser();

    void Err(std::string error_text);
    void Msg(std::string msg_text);
    vector<Image_t> InputImages(UseMode_t given_mode);
    vector<Image_t> InputDir(UseMode_t given_mode);

    bool ShowImages(vector <Image_t> what_to_show);
    //bool TestSamples (const char *path_to_dir);
    //vector <Image_t> TestUser ();
    //bool LearnNewSamples (const char *path_to_dir);
  private:
    void PrintInvitation();

};




#endif //__SPOKESMAN_H__
