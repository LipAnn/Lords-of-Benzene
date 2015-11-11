#include "CommonHeader.h"
#include "SamplesGenerator.h"

SamplesGenerator::SamplesGenerator(int seed)
{
    srand (seed);
    
}
ImagePack_t SamplesGenerator::GenerateSamples(int total_num, int with_benzol_num)
{

}

int SamplesGenerator::ObfuscateSamples(ImagePack_t* samples_ptr)
{

}

bool SamplesGenerator::SaveSamplesToFile(ImagePack_t* samples_ptr, const char* dir_path)
{

}
