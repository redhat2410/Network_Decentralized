#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <stdio.h>

typedef unsigned char   byte;
typedef unsigned int    word;

#define DEBUG

//detect platform os
#if defined(__linux__)
    #define PLATFORM_NAME   "linux"
#elif defined(_WIN32)
    #define PLATFORM_NAME   "windows"
#elif defined(_WIN64)
    #define PLATFORM_NAME   "windows"
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME   "windows"
#endif

#endif