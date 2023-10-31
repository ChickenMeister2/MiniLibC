#ifndef	__TIME_H__
#define	__TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

typedef struct timespec {
    long tv_sec;  // seconds
    long tv_nsec;   // nanoseconds
} timespec;

int nanosleep(timespec *rqtp, timespec *rmtp);
unsigned int sleep(unsigned int seconds);

#ifdef __cplusplus
}
#endif

#endif
