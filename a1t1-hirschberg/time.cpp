#include "time.h"
#ifdef _WIN32
unsigned long mtime()
{ // return the number of milliseconds since the system was started
    return GetTickCount();
}
#else
unsigned long mtime()
{ // return the number of milliseconds since epoch
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) return 0;
    return (unsigned long)((tv.tv_sec * 1000ul) + (tv.tv_usec / 1000ul));
}
#endif

unsigned long time_elapsed()
{
    static unsigned long t = 0;
    if (!t) {
        t = mtime();
        return 0;
    } else {
        unsigned long e = mtime() - t;
        t += e;
        return e;
    }
}
