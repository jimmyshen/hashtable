#ifdef DEBUG

#include <stdio.h>
#define VTRACE(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);
#define TRACE(s) fprintf(stderr, s);

#else

#define VTRACE(fmt, ...)
#define TRACE(s)

#endif

