#ifndef __TIME_H__
#define __TIME_H__

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define DEFAULT_YEAR    1900

typedef struct datetime{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t day;
    uint8_t mon;
    uint8_t year;
}datetime;

/**
 * function gettime get current time in system
 * @return      function is return struct datetime
*/
datetime get_currenttime(void);

#endif