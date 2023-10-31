// SPDX-License-Identifier: BSD-3-Clause
//https://www.informit.com/articles/article.aspx?p=23618&seqNum=11

#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
    timespec tv;
    tv.tv_sec = seconds;
    tv.tv_nsec = 0;

	while (1) {
		int rval = nanosleep(&tv, &tv);
		if (rval == 0)
			return 0;
		else if (errno == EINTR)
			continue;
		else
		return rval;
	}
	return 0;
}

