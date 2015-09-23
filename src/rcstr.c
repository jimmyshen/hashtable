#include <string.h>
#include <stdlib.h>

#include "rcstr.h"


char* rcstr_new(char *s) {
  struct RCStr* rcstr = NULL;
  size_t len = strlen(s);
  
  if (!(rcstr = malloc(sizeof(struct RCStr) + len + 1)))
    return NULL;

  rcstr->len = len;
  rcstr->refcount = 1;
  strcpy(rcstr->buf, s);

  return rcstr->buf;
}

int rcstr_incref(char *rcs) {
  struct RCStr *rcstr = (void*)(rcs - sizeof(struct RCStr));
  if (rcstr->refcount == 0) return 0;
  return ++(rcstr->refcount);
}

/* Decrease refcount. If refcount == 0, string is deallocated and further access is invalid dereference. */
int rcstr_decref(char *rcs) {
  struct RCStr *rcstr = (void*)(rcs - sizeof(struct RCStr));
  if (--rcstr->refcount == 0) {
    free(rcstr);
    return 0;
  }
  return rcstr->refcount;
}

/* Return length of string. O(1) operation since we store the length of the string. */
size_t rcstr_len(char *rcs) {
  return ((struct RCStr*)(rcs - sizeof(struct RCStr)))->len;
}

/* Return reference count of string. O(1) operation. */
size_t rcstr_refcount(char *rcs) {
  return ((struct RCStr*)(rcs - sizeof(struct RCStr)))->refcount;
}

