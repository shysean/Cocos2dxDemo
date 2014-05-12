//
//  TimeUtil.cpp
//  MyCocosDemo
//
//  Created by shihongyang on 5/12/14.
//
//

#include "TimeUtil.h"
#include <sys/time.h>

long long TimeUtil::currentTimeMillis()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
