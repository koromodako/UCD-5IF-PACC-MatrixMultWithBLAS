/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
File:   time_macro.h
Author: koromodako
Date:   2016-10-05
Purpose:
    Contains macros helpers to time operations in a C program.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef TIME_MACRO_H
#define TIME_MACRO_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define DECL_TIMEIT_VARS()   \
    struct timeval tv1, tv2; \
    struct timezone tz;      \
    double elapsed

#define TIMEIT(format_string, ret, function, ...)                             \
    gettimeofday(&tv1, &tz);                                                  \
    ret = function(__VA_ARGS__);                                              \
    gettimeofday(&tv2, &tz);                                                  \
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) +                              \
              (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;                     \
    printf(format_string, elapsed)

#endif /*TIME_MACRO_H*/
