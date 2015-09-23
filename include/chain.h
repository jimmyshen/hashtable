/**
 * Chain implementation -- a linked chain of RCStr pairs.
 *
 * Copyright (c) 2015 Jimmy Shen
 */

#ifndef _CHAIN_H
#define _CHAIN_H

#include <stdlib.h>
#include <stdbool.h>

struct ChainNode {
  char *key, *value;
  struct ChainNode *next;
};

typedef struct {
  size_t length;
  struct ChainNode *head;
} Chain;

/* Creates a new chain object on the heap. */
Chain* chain_new(void);

/* Adds a new key value pair at the head of the chain; O(1) since we always maintain
 * a pointer to the head of the chain. */
void chain_add(Chain *chain, char *k, char *v);

/* Gets the value of a key if it exists. If not, returns NULL. O(n) */
char* chain_find(Chain *chain, char *k);

/* Updates/inserts value of a key if it exists. O(n) */
void chain_update(Chain *chain, char *k, char *v);

/* Clears all items from the chain, decrementing refcounts for all key value pairs. O(n) */
void chain_clear(Chain *chain);

/* Destroys chain, decrementing refcounts for all key value pairs. */
void chain_destroy(Chain *chain);

#endif

