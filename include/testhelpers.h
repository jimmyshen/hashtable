#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void testfail(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  exit(1);
}

#endif

