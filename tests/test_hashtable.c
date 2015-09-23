
#include <string.h>

#include "testhelpers.h"
#include "hashtable.h"


void expect_to_get(HashTable *ht, char *key, char *expected) {
  char *actual;
  if ((actual = hashtable_get(ht, key))) {
    if (strcmp(expected, actual) != 0)
      testfail("get(\"%s\") should retrieved \"%s\", got \"%s\" instead", key, expected, actual);
  } else {
    testfail("get(\"%s\") should retrieved \"%s\", got NULL instead", key, expected);
  }
}


int main(void) {
  size_t initcap = 10;
  HashTable *newht, *ht = hashtable_new(initcap);

  if (!ht)
    testfail("Could not create hash table!");

  if (ht->items != 0)
    testfail("New hash table should be empty, instead has size %lu", ht->items);

  hashtable_put(ht, "Elvis", "Presley");
  if (ht->items != 1)
    testfail("Hash table should have size 1 after put instead has size %lu", ht->items);
  expect_to_get(ht, "Elvis", "Presley");

  hashtable_put(ht, "Elvis", "Costello");
  if (ht->items != 1)
    testfail("Hash table should have remained size 1 after put instead has size %lu", ht->items);
  expect_to_get(ht, "Elvis", "Costello");

  hashtable_put(ht, "Janis", "Joplin");
  if (ht->items != 2)
    testfail("Hash table should have grown to size 2 after put instead has size %lu", ht->items);
  expect_to_get(ht, "Janis", "Joplin");

  newht = hashtable_rehash(ht, 100);
  if (newht != ht)
    testfail("Expected hashtable instance to be the same; should not have changed!");

  newht = hashtable_rehash(ht, 0);
  if (newht == ht)
    testfail("Expected hashtable instance to be the different; should have changed!");

  ht = newht;

  if (newht->capacity <= initcap)
    testfail("Expected new hashtable to be larger than %lu, instead got %lu", initcap, newht->capacity);

  if (newht->items != 2)
    testfail("Expected 2 items in new hash table!");

  expect_to_get(ht, "Elvis", "Costello");
  expect_to_get(ht, "Janis", "Joplin");

  hashtable_destroy(ht);

  return 0;
}


