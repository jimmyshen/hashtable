/* A simple reference-counted string object. */

#ifndef RCSTR_H
#define RCSTR_H

struct RCStr {
  size_t len;
  size_t refcount;
  char   buf[];
};


/* Creates a new refcounted string by copying an existing one. */
char* rcstr_new(char *s);

/* Increase refcount. If refcount is already at 0, does nothing and returns false. */
int rcstr_incref(char *rcs);

/* Decrease refcount. If refcount == 0, string is deallocated and further access is invalid dereference. */
int rcstr_decref(char *rcs);

/* Return length of string. O(1) operation since we store the length of the string. */
size_t rcstr_len(char *rcs);

/* Return reference count of string. O(1) operation. */
size_t rcstr_refcount(char *rcs);

#endif

