/**
 * A small library allowing execution time measurement
 */

#ifndef TIME_H
#define TIME_H
#include <cstddef>
#ifdef _WIN32
#include <windows.h>
unsigned long mtime();
#else
#include <sys/time.h>
unsigned long mtime();
unsigned long utime();
#endif
class Clock {
    unsigned long t;
public:
    Clock();
    unsigned long elapsed();
};
#endif
