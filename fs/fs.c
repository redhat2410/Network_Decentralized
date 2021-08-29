#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "fs.h"

char* make_path_file(char* folder, char* name, char* extension){
    int len_folder = strlen(folder);
    int len_name = strlen(name);
    int len_extension = strlen(extension);

    char* l_path = (char*)malloc((len_folder + len_name + len_extension) * sizeof(char));
    // copy folder to long path
    memcpy(&l_path[0], folder, len_folder * sizeof(char));
    // copy name file to long path
    memcpy(&l_path[len_folder], name, len_name * sizeof(char));
    // copy extension to long path
    memcpy(&l_path[len_folder + len_name], extension, len_extension * sizeof(char));

    return l_path;
}