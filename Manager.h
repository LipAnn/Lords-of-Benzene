#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "CommonHeader.h"
#include "Spokesman.h"
#include "InputProcessor.h"
#include "NeuralDetector.h"
#include "NeuralYoda.h"

class Manager {
  private:
    Spokesman spokesman;
    InputProcessor processor;
    NeuralDetector detector;
    NeuralYoda yoda;
  
    vector <Image_t> LaunchSpokesman ();
    vector <Image_t> SendImagesToProc (vector <Image_t> ImagePack);
    vector <Image_t> DetectImages ();
    void SummonYoda ();
    
  public:
    
    void InitSystem ();
    void Process ();
    void BurnSystemDown ();
};

#endif //__MANAGER_H__