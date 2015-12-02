#include "Spokesman.h"
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * 
 *TODO: 
 * 1. Insert Qt4 GUI
 * 
 * 
**/

UseMode_t Spokesman::InteractWithUser()
{
    printf ("Welcome, User! Choose one of the options below:\n");
    printf ("1. Process several images\n");
    printf ("2. Train our system on your samples\n");
    printf ("3. Test the work of our system on basic sets of examples\n");
    printf ("4. Quit");
    
    char option = 0;
    
    while ( (option = getchar() - '1') > 4 || option < 0) {
        printf ("ERROR! Wrong option:\"%c\" Maybe mistyped?\n", option);
        sleep (2);
        rewind (stdout);
        ftruncate (1, 0);
        
        printf ("Welcome, User! Choose one of the options below:\n");
        printf ("1. Process several images\n");
        printf ("2. Process images in directory\n");
        printf ("3. Train our system on your samples\n");
        printf ("4. Test the work of our system on basic sets of examples\n");
        printf ("5. Quit");
    }
    
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
            printf ("What a pity that you have finally finished your work...\n");
            sleep (3);
            return UM_IM_QUIT;
            break;
    }
}

void Spokesman::Err (const char *error_text)
{
    printf ("ERROR! \"%s\"\n", error_text);
    sleep (3);
    
}
void Spokesman::Msg (const char *msg_text)
{
    printf ("MSG: %s\n", msg_text);
    sleep (3);
}

bool Spokesman::ShowImages (vector <Image_t> what_to_show)
{
    for (int i = 0; i < what_to_show.size(); i++) {
        //Displaying images
    }
}

vector <Image_t> Spokesman::InputImages (UseMode_t given_mode)
{
    char *path[PATH_MAX];
    printf ("Enter image path: ");
    Image_t new_elem;
    
    vector <Image_t> samples_vec;
    samples_vec.reserve(10);
    
    while (!scanf ("%[^\n]\n", path)) {
        new_elem.image = cv::imread (path, CV_LOAD_IMAGE_UNCHANGED);
        new_elem.info = SI_UNDEF;
        samples_vec.push_back(new_elem);
        
        printf ("Enter image path: ");
    }
    
    return samples_vec;
}

vector <Image_t> Spokesman::InputDir (UseMode_t given_mode)
{
    char *path_to_dir[PATH_MAX];
    printf ("Enter path to dir: ");
    scanf ("%[^\n]\n", path_to_dir);
    
    vector <Image_t> samples_vec;
    samples_vec.reserve(10);
    
    DIR* directory = opendir (path_to_dir);
    char path[PATH_MAX] = {};
    struct dirent *dd = NULL;
    struct stat stb;
    
    Image_t new_elem;
    if (given_mode == UM_INPUT_DIR) {
        while ((dd = readdir(directory)) != NULL) {
            snprintf (path, sizeof(path), "%s/%s", path_to_dir, dd->d_name);
            if ( (lstat (path, &stb) != -1) && S_ISREG(stb.st_mode)) {
                new_elem.image = cv::imread (path, CV_LOAD_IMAGE_UNCHANGED);
                new_elem.info = SI_UNDEF;
                samples_vec.push_back(new_elem);
            }
        }
    } else if (given_mode == UM_TRAIN_ON_NEW || given_mode == UM_TEST_SAMPLES) {
        snprintf (path, sizeof (path), "%s/%s.dat", path_to_dir, path_to_dir);
        if (!fopen (path)) {
            samples_vec.resize (0);
            return samples_vec;
        }
        FILE *input_data = fopen (path, "r");
        while (!feof (input_data)) {
            fscanf (input_data, "%s %d\n", path, &(new_elem.info));
            new_elem.image = cv::imread (path, CV_LOAD_IMAGE_UNCHANGED);
            samples_vec.push_back (new_elem);
        }
        fclose (input_data);
        return samples_vec;
    }
}