#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "hashtable.h"

#define BUCKETIDX(ht, s) (ht->hashfunc(s) % ht->capacity)


/* stolen from http://www.cse.yorku.ca/~oz/hash.html */
uint32_t hashstring(char *s) {
  uint32_t hash = 5381;
  char c;

  while ((c = *s++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

HashTable* hashtable_new(size_t capacity) {
  if (capacity < 1) return NULL;
  HashTable *ht = malloc(sizeof(HashTable) + capacity * sizeof(Chain*));
  if (ht != NULL) {
    ht->items = 0;
    ht->capacity = capacity;
    ht->hashfunc = &hashstring;
    for (size_t i = 0; i < capacity; ++i)
      ht->buckets[i] = NULL;
  }

  return ht;
}

void hashtable_put(HashTable *ht, char *k, char *v) {
  if (!ht) return;
  size_t idx = BUCKETIDX(ht, k);
  VTRACE("Hashing \"%s\" into index %lu\n", k, idx);
  if (ht->buckets[idx] == NULL) {
    chain_add(ht->buckets[idx] = chain_new(), k, v);
    ht->items++;
  } else {
    ht->items -= ht->buckets[idx]->length;
    chain_update(ht->buckets[idx], k, v);
    ht->items += ht->buckets[idx]->length;
  }
}


char* hashtable_get(HashTable *ht, char *k) {
  if (!ht) return NULL;
  size_t idx = BUCKETIDX(ht, k);
  VTRACE("Looking for \"%s\" at index %lu\n", k, idx);
  if (ht->buckets[idx] != NULL)
    return chain_find(ht->buckets[idx], k);

  return NULL;
}

HashTable *hashtable_rehash(HashTable *ht, float threshold) {
  if (!ht) return NULL;
  if (((float)ht->items / ht->capacity) < threshold) return ht;

  HashTable *newht = hashtable_new(ht->capacity << 1);
  if (!newht) return ht;
  newht->hashfunc = ht->hashfunc;

  VTRACE("Rehashing table with %lu items\n", ht->items);
  size_t idx;
  for (size_t i = 0; i < ht->capacity; ++i) {
    if (!ht->buckets[i]) continue;
    for (struct ChainNode *node = ht->buckets[i]->head; node; node = node->next) {
      idx = BUCKETIDX(newht, node->key);
      if (!newht->buckets[idx])
        newht->buckets[idx] = chain_new();

      chain_add_rcs(newht->buckets[idx], node->key, node->value);
      newht->items++;
    }

    chain_clear(ht->buckets[i]);
  }

  hashtable_destroy(ht);

  return newht;
}

void hashtable_destroy(HashTable *ht) {
  if (!ht) return;
  for (size_t i = 0; i < ht->capacity; ++i) {
    if (!ht->buckets[i]) continue;
    chain_destroy(ht->buckets[i]);
  }
  VTRACE("Destroyed table at %p\n", ht);

  free(ht);
}


