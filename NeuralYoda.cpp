#include "NeuralYoda.h"
//...

NeuralYoda::NeuralYoda(NeuralDetector* nd_ptr, int sgen_seed) :
                        padavan_ptr(nd_ptr),
                        s_generator(sgen_seed)
{
}

void NeuralYoda::LoadSamples(const char* train_dir)
{
    
}

void NeuralYoda::TrainPadavan (TrainMethod_t train_method, void *args);
    

ImagePack_t* NeuralYoda::RunSGenerator ()
{
};

bool NeuralYoda::CheckPadavan()
{

}

void NeuralYoda::Meditate()
{

}