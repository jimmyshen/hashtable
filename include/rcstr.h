/* A simple reference-counted string object. */

#ifndef _RCSTR_H
#define _RCSTR_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct RCStr {
  long  len;
  long  refcnt;
  char  buf[];
};


/* Creates a new refcounted string by copying an existing one. */
char* rcstr_new(char *s) {
  struct RCStr* rcstr = NULL;
  size_t len = strlen(s);
  
  if (!(rcstr = malloc(sizeof(struct RCStr) + len + 1)))
    return NULL;

  rcstr->len = len;
  rcstr->refcnt = 1;
  strcpy(rcstr->buf, s);
  return rcstr->buf;
}

/* Increase refcount. If refcount is already at 0, does nothing and returns false. */
int rcstr_incref(char *rcs) {
  struct RCStr *rcstr = (void*)(rcs - sizeof(struct RCStr));
  if (rcstr->refcnt == 0) return 0;
  return ++(rcstr->refcnt);
}

/* Decrease refcount. If refcount == 0, string is deallocated and further access is invalid dereference. */
int rcstr_decref(char *rcs) {
  struct RCStr *rcstr = (void*)(rcs - sizeof(struct RCStr));
  if (--rcstr->refcnt == 0) {
    free(rcstr);
    return 0;
  }
  return rcstr->refcnt;
}

/* Return length of string. O(1) operation since we store the length of the string. */
size_t rcstr_len(char *rcs) {
  return ((struct RCStr*)(rcs - sizeof(struct RCStr)))->len;
}

/* Return reference count of string. O(1) operation. */
int rcstr_refcount(char *rcs) {
  return ((struct RCStr*)(rcs - sizeof(struct RCStr)))->refcnt;
}

#endif

