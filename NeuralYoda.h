
#ifndef __NEURAL_YODA_H__
#define __NEURAL_YODA_H__

enum TrainMethod_t {
    TM_TRAINDIR,
    TM_YOURSELF,
    TM_TRAINIMAGES
};

class NeuralYoda
{
  private:
    NeuralDetector *padavan_ptr;
    SamplesGenerator s_generator;
        
  public:
    NeuralYoda (NeuralDetector *nd_ptr, int sgen_seed);
    ~NeuralYoda();
    
    void LoadSamples (const char *train_dir = NULL);
    void TrainPadavan (TrainMethod_t train_method, void *args);
    ImagePack_t* RunSGenerator ();
    bool CheckPadavan ();
    void Meditate ();
};

#endif //__NEURAL_YODA_H__