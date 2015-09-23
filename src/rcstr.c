#include <string.h>
#include <stdlib.h>

#include "debug.h"
#include "rcstr.h"


char* rcstr_new(char *s) {
  struct RCStr* rcstr = NULL;
  size_t len = strlen(s);
  
  if (!(rcstr = malloc(sizeof(struct RCStr) + len + 1)))
    return NULL;

  VTRACE("Created \"%s\" (%p)\n", s, rcstr);

  rcstr->refcount = 1;
  strcpy(rcstr->buf, s);

  return rcstr->buf;
}

int rcstr_incref(char *rcs) {
  struct RCStr *rcstr = (void*)(rcs - sizeof(struct RCStr));
  if (rcstr->refcount == 0) return 0;
  VTRACE("Increasing reference count for \"%s\" (%p)\n", rcs, rcs);
  return ++(rcstr->refcount);
}

/* Decrease refcount. If refcount == 0, string is deallocated and further access is invalid dereference. */
int rcstr_decref(char *rcs) {
  struct RCStr *rcstr = (void*)(rcs - sizeof(struct RCStr));
  VTRACE("Decreasing reference count for \"%s\" (%p)\n", rcs, rcs);
  if (--rcstr->refcount == 0) {
    VTRACE("Freeing \"%s\" (%p)\n", rcs, rcs);
    free(rcstr);
    return 0;
  }
  return rcstr->refcount;
}

/* Return reference count of string. O(1) operation. */
refcount rcstr_refcount(char *rcs) {
  return ((struct RCStr*)(rcs - sizeof(struct RCStr)))->refcount;
}

