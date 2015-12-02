#include "Manager.h"
/**
 * 
 * 
 * 
 * 
**/

void Manager::SummonYoda ()
{
    
}

void Manager::InitSystem ()
{
// Here we will insert some of init functions if there will be any in this project 
}

void Manager::Process ()
{
    InitSystem ();
    
    UseMode_t given_mode;
    while (1) {
        given_mode = spokesman.InteractWithUser();
        vector <Image_t> samples_vec;
        switch (given_mode) {
            case UM_INPUT_IMAGE:
                samples_vec = detector.DetectImages (processor.ProcessImages (spokesman.InputImages()) );
                spokesman.ShowImages (samples_vec);
                break;
            
            case UM_INPUT_DIR:
                samples_vec = detector.DetectImages (processor.ProcessImages (spokesman.InputDir()) );
                spokesman.ShowImages (samples_vec);
                break;
                
            case UM_TRAIN_ON_NEW:
                if (!SummonYoda (samples_vec, given_mode) ) {
                    spokesman.Err ("Cannot train neural system!");
                } else {
                    spokesman.Msg ("Train was successfully ended!");
                }
                break;
                
            case UM_TEST_SAMPLES:
                if (!SummonYoda (samples_vec, given_mode) ) {
                    spokesman.Err ("System has mistaken in basic tests...Shame on us!");
                } else {
                    spokesman.Msg ("Basic tests were passed successfully");
                }
                break;
                
            case UM_IM_QUIT:
                BurnSystemDown();
                return;
                break;
                
            default:
                spokesman.Err ("Unknown mode!");
                return;
        }
    }
}

void Manager::BurnSystemDown ()
{
    // Here we will insert some of destroying functions if there will be any in this project   
}