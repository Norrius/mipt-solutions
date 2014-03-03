/**
 * A small library allowing execution time measurement
 */

#ifndef TIME_H
#define TIME_H
#include <cstddef>
#ifdef _WIN32
#include <winbase.h>
unsigned long mtime();
#else
#include <sys/time.h>
unsigned long mtime();
unsigned long utime();
#endif

unsigned long time_elapsed();
#endif
