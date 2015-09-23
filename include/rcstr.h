/* A simple reference-counted string object. */

#ifndef RCSTR_H
#define RCSTR_H

#include <stdint.h>

typedef unsigned char refcount;

struct RCStr {
  refcount refcount;
  char     buf[];
};


/* Creates a new refcounted string by copying an existing one. */
char* rcstr_new(char *s);

/* Increase refcount. If refcount is already at 0, does nothing and returns false. */
int rcstr_incref(char *rcs);

/* Decrease refcount. If refcount == 0, string is deallocated and further access is invalid dereference. */
int rcstr_decref(char *rcs);

/* Return reference count of string. O(1) operation. */
refcount rcstr_refcount(char *rcs);

#endif

