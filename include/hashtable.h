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

HashTable*  hashtable_new(size_t capacity);
void        hashtable_put(HashTable *ht, char *k, char *v);
char*       hashtable_get(HashTable *ht, char *k);
HashTable*  hashtable_rehash(HashTable *ht, float threshold);
void        hashtable_destroy(HashTable *ht);

#endif

