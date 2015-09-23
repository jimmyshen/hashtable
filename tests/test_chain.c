#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "testhelpers.h"
#include "chain.h"

struct {
  char *k, *v;
} items[] = {
  {"Alice", "In Chains"},
  {"Bob", "Hope"},
};


int main(void) {
  Chain *chain;

  if ((chain = chain_new()) == NULL)
    testfail("Failed to create new chain object!");

  if (chain->length != 0)
    testfail("Expected new chain to be empty, instead has length %lu", chain->length);

  chain_add(chain, items[0].k, items[0].v);
  if (chain->length != 1)
    testfail("Expected added item to have length 1, instead has length %lu", chain->length);

  chain_add(chain, items[1].k, items[1].v);
  if (chain->length != 2)
    testfail("Expected added item to have length 2, instead has length %lu", chain->length);

  if (chain_update(chain, items[1].k, items[0].v) != true)
    testfail("Expected update of key %s to succeed", items[1].k);

  if (chain->length != 2)
    testfail("Expected chain length to remain 2, instead has length %lu", chain->length);

  chain_clear(chain);
  if (chain->length != 0)
    testfail("Expected cleared chain to have length 0, instead has length %lu", chain->length);

  chain_destroy(chain);

  return 0;
}

