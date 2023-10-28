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
		int rval = nanosleep (&tv, &tv);
		if (rval == 0)
		/* Completed the entire sleep time; all done. */
			return 0;
		else if (errno == EINTR)
		/* Interrupted by a signal. Try again. */
			continue;
		else 
		/* Some other error; bail out. */
		return rval;
	}
 	return 0;
}

