#ifndef TIMESPEC_HPP
#define TIMESPEC_HPP

//custom includes

//global includes
#include <ctime>

#ifdef _WIN32
    #include <windows.h>

extern LARGE_INTEGER getFILETIMEoffset();

extern int clock_gettime(int X, struct timeval *tv);

#else

extern int clock_gettime(int X, struct timeval *tv);

#endif

#endif // TIMESPEC_HPP
