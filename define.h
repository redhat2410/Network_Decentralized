#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <stdio.h>
#include "blockchain/block.h"
#include "times/datetime.h"

typedef unsigned char   BYTE;
typedef unsigned int    WORD;
typedef BYTE            BOOL;

/**************** define macro for common ****************/
#define DEBUG
#define TRUE    1
#define FALSE   0

/***************** define value default *****************/
// const data __default_data = {.length = 0, .value = { 0 } };
// #define DEFAULT_DATA __default_data

//detect platform os
#if defined(__linux__)
    #define PLATFORM_NAME   "linux"
    #define DEFAULT_FOLDER  "./"
#elif defined(_WIN32)
    #define PLATFORM_NAME   "windows"
#elif defined(_WIN64)
    #define PLATFORM_NAME   "windows"
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME   "windows"
#endif

#endif