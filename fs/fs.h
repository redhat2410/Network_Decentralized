#ifndef __FS_H__
#define __FS_H__

#include <stdio.h>

/**
 * function make_path_file use to create path link to file
 * @param folder            folder store file
 * @param name              name file
 * @param extension         extension of file
*/
char* make_path_file(char* folder, char* name, char* extension);
void print_string(char* str, int length);
#endif