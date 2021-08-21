#include <stdio.h>
#include "datetime.h"

datetime get_currenttime(void){
    datetime ret; //struct data to return
    time_t rawtime;
    struct tm *timeinfo;

    //init time 
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    // write time in struc datetime
    ret.hour    = (uint8_t)timeinfo->tm_hour;
    ret.min     = (uint8_t)timeinfo->tm_min;
    ret.sec     = (uint8_t)timeinfo->tm_sec;
    ret.day     = (uint8_t)timeinfo->tm_mday;
    ret.mon     = (uint8_t)timeinfo->tm_mon;
    ret.year    = (uint8_t)timeinfo->tm_year;
    // return datetime
    return ret;
}

