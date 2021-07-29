// timer.cpp (modified by shanjb20)

/**
 * @file timer.cpp
 * @Synopsis  Implatition of Timer class
 * @author Hailong Yao
 * @version 1
 * @date 2015-09-25
 */
#include "timer.h"

#include <climits>
#ifdef _POSIX_ARG_MAX
#include <unistd.h>
#ifdef _POSIX_VERSION
#ifdef _XOPEN_UNIX
#define __GETRUSAGE__
#endif
#endif
#endif

#ifdef __GETRUSAGE__
#include <sys/resource.h>
#else
#include <ctime>
#endif

#include <cfloat>
#include <iostream>

double Timer::getUserTime() const {
#ifdef __GETRUSAGE__
    struct rusage usage;
    int ret = getrusage(RUSAGE_SELF, &usage);
    if (ret == 0)
        return double(usage.ru_utime.tv_sec)                 // seconds
               + double(usage.ru_utime.tv_usec) / 1000000.0; // microseconds
    else
        throw new Error("Timer : Call to getrusage() failed", 4001);
#else
    std::clock_t clk = std::clock();
    if (clk != (std::clock_t)-1)
        return double(clk) / CLOCKS_PER_SEC;
    else
        throw new Error("Timer : Call to clock() failed", 4002);
#endif
    throw new Error("Timer : Unknown ERROR", 4000);
    return 0.0;
}

double Timer::getPrecision() const {
    double min_res = DBL_MAX;
    for (int i = 0; i < 5; ++i) {
        double current = getUserTime();
        double next = getUserTime();
        while (current >= next) // wait until timer increases
            next = getUserTime();
        // Get the minimum timing difference of all runs.
        if (min_res > next - current)
            min_res = next - current;
    }
    return min_res;
}

double Timer::precision() const {
    static double prec = getPrecision();
    return prec;
}
