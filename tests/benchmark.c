#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

void timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;
}


void print_elapsed(const char *name, const struct timeval *tv) {
  struct timeval end, result;
  gettimeofday(&end, NULL);
  timeval_subtract(&result, &end, tv);
  long ms = result.tv_sec * 1000 + result.tv_usec / 1000;
  printf("%s completed in %dms\n", name, ms);
}


int main(void) {
  printf("Generating test strings...\n");
  size_t cap = 3;
  unsigned int n, m, i;

  char inputs[10000][32];
  for (i = 0; i < 10000; ++i)
    sprintf(inputs[i], "%X", i);

  HashTable *ht;
  struct timeval begin;

  m = 100;
  for (n = 0; n < 3; ++n) {
    printf("Capacity of %lu with %u items\n", cap, m);
    ht = hashtable_new(cap);
    gettimeofday(&begin, NULL);
    for (i  = 0; i < m; ++i)
      hashtable_put(ht, inputs[i], inputs[i]);
    print_elapsed("PUTS", &begin);

    printf("Size is now %lu\n", ht->items);

    gettimeofday(&begin, NULL);
    for (i  = 0; i < m; ++i)
      hashtable_get(ht, inputs[i]);
    print_elapsed("GETS", &begin);

    hashtable_destroy(ht);

    m *= 10;
    cap *= 10;

    printf("\n");
  }

  return 0;
}
