// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int puts(const char *s) {

    size_t len = strlen(s);
    if (write(STDOUT_FILENO, s, len) != len) {
        return EOF;
    }
    if(write(STDOUT_FILENO, "\n", 1) != 1) {
        return EOF;
    }   
    return 1;
}

