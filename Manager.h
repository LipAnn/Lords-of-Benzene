#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "CommonHeader.h"
#include "Spokesman.h"
#include "InputProcessor.h"
#include "NeuralDetector.h"

class Manager {
  private:
    Spokesman spokesman;
    InputProcessor processor;
    NeuralDetector detector;

    void InitSystem ();
    void BurnSystemDown ();

  public:
    void Process ();
};

#endif //__MANAGER_H__
