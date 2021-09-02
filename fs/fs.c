#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "fs.h"
#include "../crypto/sha256.h"

char* make_path_file(char* folder, char* name, char* extension){
    int len_folder = strlen(folder);
    int len_name = strlen(name);
    int len_extension = strlen(extension);
    char* l_path = (char*)malloc((len_folder + len_name + len_extension + 1) * sizeof(char));
    // concat chain
    strcpy(&l_path[0], folder);
    strcpy(&l_path[len_folder], name);
    if(len_name == (SHA256_BLOCK_SIZE * 2))
        strcpy(&l_path[len_folder + len_name], extension);
    else
        strcpy(&l_path[len_folder + len_name - 1], extension);
    // return long path
    return l_path;
}

void print_string(char* str, int length){
    for(int i = 0; i < length; i++)
        printf("%c", str[i]);
    printf("\n");
}