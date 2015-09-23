#include <stdlib.h>
#include <string.h>

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
  if (ht->buckets[idx] != NULL)
    return chain_find(ht->buckets[idx], k);

  return NULL;
}

HashTable *hashtable_rehash(HashTable *ht, float threshold) {
  if (!ht) return NULL;
  if (((float)ht->items / ht->capacity) < threshold) return ht;

  HashTable *newht = hashtable_new(ht->capacity << 1);
  if (!newht) return ht;

  for (size_t i = 0; i < ht->capacity; ++i) {
    if (!ht->buckets[i]) continue;
    for (struct ChainNode *node = ht->buckets[i]->head; node; node = node->next)
      hashtable_put(newht, node->key, node->value);

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

  free(ht);
}


