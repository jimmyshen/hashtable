This is a simple chained hash table written in C.

Use of refcounted strings
-------------------------

I decided to use a reference counted string type to manage strings kept in the hash table chains.
These are defined entirely in `rcstr.h`. By using a reference count, the chain does not need to be
involved in memory management when the heap-allocated string references are copied during a rehashing
operation.

I also borrowed ideas from antirez's SDS implementation in Redis [http://redis.io/topics/internals-sds] so that
these strings can be treated as regular C strings but their refcount metadata could be accessed with the
right interfaces.


Customizable hash function
--------------------------

It is possible to override the default string hashing function by setting the `hashfunc` member of a `HashTable` with
the interface `(uint32_t)(*hashfunc)(char*)`. Subsequent operations on the hash table will use the provided hash
function. Of course, this must be done immediately before the hash table is populated to prevent inconsistencies.


Rehashing
---------

Rehashing is not an automatic operation and must be triggered manually by calling the `rehash(HashTable*, float)`
function. This method accepts a single parameter that defines a load threshold. By default, this is 4.0, meaning that
`n_items / n_buckets` must be greater than or equal to this value in order to rehash. To force a rehash, simply pass
`0` to this method.

