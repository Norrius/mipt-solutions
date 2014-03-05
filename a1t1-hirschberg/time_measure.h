/**
 * A small library allowing execution time measurement
 */

#ifndef TIME_H
#define TIME_H
#include <cstddef>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
unsigned long mtime();
class Clock {
    unsigned long t;
public:
    Clock();
    unsigned long elapsed();
};
#endif
