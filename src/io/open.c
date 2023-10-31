// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
    int res = syscall(__NR_open, filename, flags);
    if (res < 0) {
        errno = -res;
        return -1;
    }
    return res;
}
