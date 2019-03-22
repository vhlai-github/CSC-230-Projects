#include <unistd.h>

/** A replacement for the usleep() call.  Linking with this file should
    replace the standard usleep(), speeding up execution on the lartest
    test case.
    @param usec desired sleep time, ignored in this version.
    @return always returns zero.
 */
int usleep( useconds_t usec )
{
  return 0;
}
