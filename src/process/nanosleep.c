#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <time.h>

int nanosleep(timespec *rqtp,timespec *rmtp)
{
	int ret = syscall(__NR_nanosleep, rqtp, rmtp);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return 0;
}

