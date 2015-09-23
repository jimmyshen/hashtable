#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "testhelpers.h"
#include "rcstr.h"

static char msg[] = "hello world!";

int main(void) {
  char *rcs;

  if ((rcs = rcstr_new(msg)) == NULL)
    testfail("Failed to allocate new rcstr");

  if (strcmp(rcs, msg) != 0)
    testfail("Expected string to be copied in full: got \"%s\"", rcs);

  int refcnt = rcstr_refcount(rcs);
  if (refcnt != 1)
    testfail("Expected refcount of 1 got %d", refcnt);

  if ((refcnt = rcstr_incref(rcs)) != 2)
    testfail("Expected refcount of 2 after incref; got %d", refcnt);

  if (rcstr_decref(rcs) != 1)
    testfail("Expected first decref to return 1");

  if (rcstr_decref(rcs) != 0)
    testfail("Expected last decref to return 0");

  return 0;
}
