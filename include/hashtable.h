#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdint.h>

#include "chain.h"

typedef uint32_t(*hashfuncptr)(char*);

typedef struct {
  size_t      items;
  size_t      capacity;
  hashfuncptr hashfunc;
  Chain*      buckets[];
} HashTable;

/* Creates a new hash table with `capacity` buckets */
HashTable*  hashtable_new(size_t capacity);

/* Puts value `v` at key `k` */
void hashtable_put(HashTable *ht, char *k, char *v);

/* Gets value at key `k`; returns NULL if not found */
char* hashtable_get(HashTable *ht, char *k);

/* Rehash table if `items` / `capacity` >= `threshold`. If table is rehashed, original is
 * invalidated and client should use pointer returned by function for further operation.
 */
HashTable* hashtable_rehash(HashTable *ht, float threshold);


/* Frees memory for hashtable. Keys and values will only be freed if reference counts
 * reach zero (no other hash tables are referencing them)
 */
void hashtable_destroy(HashTable *ht);

#endif

