#ifndef __SAMPLES_GENERATOR_H__
#define __SAMPLES_GENERATOR_H__

class SamplesGenerator
{
  public:
    SamplesGenerator (int seed = 0);
    ~SamplesGenerator();
    
    ImagePack_t GenerateSamples (int total_num = 10, int with_benzol_num = 5);
    int ObfuscateSamples (ImagePack_t *samples_ptr);
    bool SaveSamplesToFile (ImagePack_t *samples_ptr, const char *dir_path);
};

#endif //__SAMPLES_GENERATOR_H__