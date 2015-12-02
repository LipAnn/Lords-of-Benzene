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
    
    void InitSystem ();
    void SummonYoda (vector <Image_t> ImagePack, UseMode_t given_mode);
    void BurnSystemDown ();
    
  public:  
    void Process ();
};

#endif //__MANAGER_H__