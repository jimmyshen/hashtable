#include <stdlib.h>
#include <string.h>

#include "rcstr.h"
#include "chain.h"


Chain* chain_new(void) {
  Chain *chain = malloc(sizeof(Chain));
  if (chain != NULL) {
    chain->length = 0;
    chain->head = NULL;
  }

  return chain;
}

void chain_add(Chain *chain, char *k, char *v) {
  if (!chain) return;

  struct ChainNode *node = malloc(sizeof(struct ChainNode));
  if (node != NULL) {
    node->key = rcstr_new(k);
    node->value = rcstr_new(v);
    node->next = chain->head;
    chain->head = node;

    chain->length++;
  }
}

char* chain_find(Chain *chain, char *k) {
  for (struct ChainNode *n = chain->head; n; n = n->next)
    if (strcmp(n->key, k) == 0)
      return n->value;

  return NULL;
}

void chain_update(Chain *chain, char *k, char *v) {
  for (struct ChainNode *n = chain->head; n; n = n->next) {
    if (strcmp(n->key, k) == 0) {
      rcstr_decref(n->value);
      n->value = rcstr_new(v);
      return;
    }
  }

  chain_add(chain, k, v);
}

void chain_clear(Chain *chain) {
  if (!chain) return;

  struct ChainNode *tmp, *n = chain->head;
  while (n) {
    tmp = n;
    n = n->next;
    rcstr_decref(tmp->value);
    rcstr_decref(tmp->key);
    free(tmp);
  }

  chain->length = 0;
  chain->head = NULL;
}

void chain_destroy(Chain *chain) {
  if (!chain) return;
  chain_clear(chain);
  free(chain);
}

