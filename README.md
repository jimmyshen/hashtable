This is a simple chained hash table written in C purely for mapping strings to strings.

Implementation notes
--------------------

- Under the hood, all strings stored in the hash table chains are actually refcounted strings (see `rcstr.h` for
  interface). This allows for an optimization to prevent expensive string copies during a rehashing at the expense
  of storing an additional byte of data per item in the table.

- Reference counted strings are passed around like normal strings and access to the refcount is managed by interfaces
  that know the negative offset of the refcount. This is something I picked up from antirez's implementation of strings
  in Redis [http://redis.io/topics/internals-sds]

- The choice of hash function can be overridden at runtime simply by setting a different function for the `hashfunc`
  member of the `HashTable` struct. This function must be of the signature `uint32_t(*hashfunc)(char*)`. Of course,
  this should be overridden *before* any hashing is done. The overridden hash function is inherited for you during
  re-hash.

- Rehashing is triggered manually via the `rehash(HashTable*, float)` function. The second argument is the threshold
  that must be met or exceeded in order for rehashing to take place. This means that `n_items / n_buckets`
  must be greater than this value. To force a rehash, simply pass `0`.

- Rehashing doubles the capacity of the hash array each time.
