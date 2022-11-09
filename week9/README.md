# First Lecture
## Heap and Priority Queues
### Heaps

Heaps can be viewed as trees with top-to-bottom ordering
- cf. binary search trees which have left-to-right ordering
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/heap-bst.png)

Heap characteristics ...
- priorities determined by order on keys
- new items added initially at lower-most, right-most leaf
- then new item "drifts up" to appropriate level in tree
- items are always deleted by removing root (top priority)

> Since heaps are dense trees, depth = floor(log2N)+1
> Insertion cost = O(logN),   Deletion cost = O(logN)

- Heaps are typically used for implementing Priority Queues

Grow in regular (level-order) manner:
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/heap-growth.png)

- Nodes are always added in sequence indicated by numbers

Trace of growing heap ...
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/heap-grow.png)

BSTs are typically implemented as linked data structures.

Heaps are often implemented via arrays   (assumes we know max size)

Simple index calculations allow navigation through the tree:
- left child of ```Item``` at index i is located at 2i
- right child of ```Item``` at index i  is located at 2i+1
- parent of ```Item``` at index i  is located at i/2
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/heap-array.png)

Heap data structure:
```
typedef struct HeapRep {
   Item *items;  // array of Items
   int  nitems;  // #items in array
   int  nslots;  // #elements in array
} HeapRep;

typedef HeapRep *Heap;
```

- Initialisation: ```nitems = 0,  nslots =```ArraySize
- One difference: we use indexes from 1..```nitems```

> Note: unlike "normal" C arrays, nitems also gives index of last item

1. Creating new heap:

```
Heap newHeap(int N)
{
   Heap new = malloc(sizeof(HeapRep));
   Item *a = malloc((N+1)*sizeof(Item));
   assert(new != NULL && a != NULL);
   new->items = a;   // no initialisation needed
   new->nitems = 0;  // counter and index
   new->nslots = N;  // index range 1..N
   return new;
}
```

### Insertion with Heaps 

Insertion is a two-step process
- add new element at next available position on bottom row (but this might violate heap property; new value larger than parent)
- reorganise values along path to root to restore heap property
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/heap-fixup.png)

Insertion into heap:

```
void HeapInsert(Heap h, Item it)
{
   // is there space in the array?
   assert(h->nitems < h->nslots);
   h->nitems++;
   // add new item at end of array
   h->items[h->nitems] = it;
   // move new item to its correct place
   fixUp(h->items, h->nitems);
}
```

2. Bottom-up heapify:

```
// force value at a[i] into correct position
void fixUp(Item a[], int i)
{
   while (i > 1 && less(a[i/2],a[i])) {
      swap(a, i, i/2);
      i = i/2;  // integer division
   }
}
void swap(Item a[], int i, int j)
{
   Item tmp = a[i];
   a[i] = a[j];
   a[j] = tmp;
}
```

Trace of ```fixUp``` after insertion ..
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/fixup-trace.png)

### Deletion with Heaps
Deletion is a three-step process:
- replace root value by bottom-most, rightmost value
- remove bottom-most, rightmost value
- reorganise values along path from root to restore heap
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/heaps/Pics/heap-fixdown.png)

1. Deletion from heap (always remove root):
```
Item HeapDelete(Heap h)
{
   Item top = h->items[1];
   // overwrite first by last
   h->items[1] = h->items[h->nitems];
   h->nitems--;
   // move new root to correct position
   fixDown(h->items, 1, h->nitems);
   return top;
}
```

2. Top-down heapify:
```
// force value at a[i] into correct position
// note that N gives max index *and* # items
void fixDown(Item a[], int i, int N)
{
   while (2*i <= N) {
      // compute address of left child
      int j = 2*i;
      // choose larger of two children
      if (j < N && less(a[j], a[j+1])) j++;
      if (!less(a[i], a[j])) break;
      swap(a, i, j);
      // move one level down the heap
      i = j;
   }
}
```

### Cost Analysis 
Recall:  tree is compact;  max path length = log2n

For insertion ...
- add new item at end of array  ⇒  O(1)
- move item up into correct position  ⇒  O(log2n)

For deletion ...
- replace root by item at end of array  ⇒  O(1)
- move new root down into correct position  ⇒  O(log2n)

### Priority Queues
Heap behaviour is exactly behaviour required for Priority Queue ...
- ```join(PQ,it)```: ensure highest priority item at front of queue
- ```it = leave(PQ)```: take highest priority item from queue
So ...
```
typedef Heap PQueue;

void join(PQueue pq, Item it) { HeapInsert(pq,it); }

Item leave(PQueue pq) { return HeapDelete(pq); }
```

- Heaps are not the only way to implement priority queues ...
- Comparison of different Priority Queue representations: [^1]

* If fixed-size array (no realloc), choose max N that might ever be needed

## Hashing 
### Associative Indexing 

Regular array indexing is positional   (```[0], [1], [2]```, ...):
- can access items by their position in an array
- but generally don't know position for an item with key K
- we need to search for the item in the collection using K
- search can be linear (0(n)) or binary (O(log2n))

An alternative approach to indexing:
- use the key value as an index ... no searching needed
- access data for item with key K as ```array[K]```

Difference between positional and associative indexing: 
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hashing/Pics/assoc-indexing.png)

### Hashing 
Hashing allows us to get close to associative indexing

1. Ideally, we would like ...
```
courses["COMP3311"] = "Database Systems";
printf("%s\n", courses["COMP3311"]);
```

but C doesn't have non-integer index values.

2. Something almost as good:
```
courses[h("COMP3311")] = "Database Systems";
printf("%s\n", courses[h("COMP3311")]);
```

> Hash function ```h``` converts key to integer and uses that as the index.

What the h (hash) function does: 
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hashing/Pics/hashing-review.png)

- Converts a key value (of any type) into an integer index.

> not so simple in practice

Reminder: what we'd like ...
```
courses[h("COMP3311")] = "Database Systems";
printf("%s\n", courses[h("COMP3311")]);
```

In practice, we do something like ...
```
key = "COMP3311";
item = {"COMP3311","Database Systems",...};
courses = HashInsert(courses, key, item);
printf("%s\n", HashGet(courses, "COMP3311"));
```

To use arbitrary values as keys, we need ...
- set of ```Key``` values dom(```Key)```,   each key identifies one ```Item```
- an array (of size N) to store ```Item```s
- a hash function h() of type dom(```Key```) → [0..N-1]
  - requirement: if (x = y)  then h(x) = h(y)
  - requirement: h(x) always returns same value for given x

A problem: array is size N,  but  dom(```Key```) ``` >> ``` N
So, we also need a collision resolution method
- collision = (x ≠ y  but  h(x) = h(y) )

### Hash Table ADT
Generalised ADT for a collection of Items

1. Interface:
```
typedef struct CollectionRep *Collection;

Collection newCollection();    // make new empty collection
Item *search(Collection, Key); // find item with key
void insert(Collection, Item); // add item into collection
void delete(Collection, Key);  // drop item with key
```

2. Implementation:
```
typedef struct CollectionRep {
   ... some data structure to hold multiple Items ...
} CollectionRep;
```

For hash tables, make one change to "standard" Collection interface:
```
typedef struct HashTabRep *HashTable;
// make new empty table of size N
HashTable newHashTable(int);
// add item into collection
void HashInsert(HashTable, Item);
// find item with key
Item *HashGet(HashTable, Key);
// drop item with key
void HashDelete(HashTable, Key);
// free memory of a HashTable
void dropHashTable(HashTable);
```

i.e. we specify max # elements that can be stored in the collection

- Example hash table implementation:
```
typedef struct HashTabRep {
   Item **items; // array of (Item *)
   int  N;       // size of array
   int  nitems;  // # Items in array
} HashTabRep;

HashTable newHashTable(int N)
{
   HashTable new = malloc(sizeof(HashTabRep));
   new->items = malloc(N*sizeof(Item *));
   new->N = N;
   new->nitems = 0;
   for (int i = 0; i < N; i++) new->items[i] = NULL;
   return new;
}

void HashInsert(HashTable ht, Item it) {
   int h = hash(key(it), ht->N);
   // assume table slot empty!?
   ht->items[h] = copy(it);
   ht->nitems++;
}

Item *HashGet(HashTable ht, Key k) {
   int h = hash(k, ht->N);
   Item *itp = ht->items[h];
   if (itp != NULL && equal(key(*itp),k))
      return itp;
   else
      return NULL;
}

void HashDelete(HashTable ht, Key k) {
   int h = hash(k, ht->N);
   Item *itp = ht->items[h];
   if (itp != NULL && equal(key(*itp),k)) {
      free(itp);
      ht->items[h] = NULL;
      ht->nitems--;
   }
}

void dropHashTable(HashTable ht) {
   for (int i = 0; i < ht->N; i++) {
      if (ht->items[i] != NULL) free(ht->items[i]);
   }
   free(ht);
}
```

```key()``` and ```copy()``` come from ```Item ``` type; ```equal()``` from ```Key``` type

### Hash Functions
Characteristics of hash functions:
- converts ```Key``` value to index value [0..N-1]
- deterministic (key value k always maps to same value)
- <b> use ```mod``` function to map hash value to index value </b>
- spread key values uniformly over address range (assumes that keys themselves are uniformly distributed)
- as much as possible, h(k) ≠ h(j)  if j ≠ k
- cost of computing hash function must be cheap

- Basic mechanism of hash functions:
```
int hash(Key key, int N)
{
   int val = convert key to 32-bit int;
   return val % N;
}
```
- If keys are ```int```s, conversion is easy (identity function)
- How to convert keys which are strings?   (e.g. "COMP1927" or "John")
- Definitely prefer that  hash("cat",N)  ≠  hash("dog",N)
- Prefer that  hash("cat",N)  ≠  hash("act",N)  ≠  hash("tac",N)

Universal hashing uses entire key, with position info:
```
int hash(char *key, int N)
{
   int h = 0, a = 31415, b = 21783;
   char *c;
   for (c = key; *c != '\0'; c++) {
      a = a*b % (N-1);
      h = (a * h + *c) % N;
   }
   return h;
}
```
Has some similarities with RNG.  
> Aim: "spread" hash values over [0..N-1]

A real hash function (from PostgreSQL DBMS):
```
#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8);  \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12); \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5);  \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

hash_any(unsigned char *k, register int keylen, int N)
{
   register uint32 a, b, c, len;
   // set up internal state
   len = keylen;
   a = b = 0x9e3779b9;
   c = 3923095;
   // handle most of the key, in 12-char chunks
   while (len >= 12) {
      a += (k[0] + (k[1] << 8) + (k[2] << 16) + (k[3] << 24));
      b += (k[4] + (k[5] << 8) + (k[6] << 16) + (k[7] << 24));
      c += (k[8] + (k[9] << 8) + (k[10] << 16) + (k[11] << 24));
      mix(a, b, c);
      k += 12; len -= 12;
   }
   // collect any data from remaining bytes into a,b,c
   mix(a, b, c);
   return c % N;
}
```

For ```mix```, it scrambles all of the bits from the bytes of the key value.

### Problems with Hashing
In ideal scenarios, search cost in hash table is O(1).

Problems with hashing:
- hash function relies on size of array (⇒ can't expand)
  - changing size of array effectively changes the hash function
  - if change array size, then need to re-insert all ```Item```s
- items are stored in (effectively) random order
- if size(KeySpace)  size(IndexSpace),  collisions inevitable
  - collision:   k ≠ j  &&  hash(k,N) = hash(j,N)
  - if ```nitems > nslots```,  collisions inevitable

## Hash Collisions
### Hashing: Reminder
Goal is to use keys as indexes, e.g.
```
courses["COMP3311"] = "Database Systems";
printf("%s\n", courses["COMP3311"]);
```

Since strings can't be indexes in C, use via a hash function, e.g.
```
courses[h("COMP3311")] = "Database Systems";
printf("%s\n", courses[h("COMP3311")]);
```

Hash function  h  converts key → integer and uses that as the index.
- Problem:   collisions,  where k ≠ j  but  hash(k,N) = hash(j,N)


### Collision Resolution

Three approaches to dealing with hash collisions:
- allow multiple Items at a single array location
   - e.g. array of linked lists   (but worst case is O(N))
- systematically compute new indexes until find a free slot
   - need strategies for computing new indexes (aka probing)
- increase the size of the array
   - needs a method to "adjust" ```hash()```   (e.g. linear hashing)

### Separate Chaining
Solve collisions by having multiple items per array entry.

Make each element the start of linked-list of Items.
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hash-collision/Pics/hash-linked.png)

All items in a given list have the same ```hash()``` value

> Example of separate chaining ...
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hash-collision/Pics/chaining.png)

1. Concrete data structure for hashing via chaining
```
typedef struct HashTabRep {
   List *lists; // array of Lists of Items
   int  N;      // # elements in array
   int  nitems; // # items stored in HashTable
} HashTabRep;

HashTable newHashTable(int N)
{
   HashTabRep *new = malloc(sizeof(HashTabRep));
   assert(new != NULL);
   new->lists = malloc(N*sizeof(List));
   assert(new->lists != NULL);
   for (int i = 0; i < N; i++)
      new->lists[i] = newList();
   new->N = N; new->nitems = 0;
   return new;
}
```

2. Using the List ADT, search becomes:

```
#include "List.h" 
Item *HashGet(HashTable ht, Key k)
{
   int i = hash(k, ht->N);
   return ListSearch(ht->lists[i], k);
}
```

Even without ```List``` abstraction, easy to implement.
> Using sorted lists gives only small performance gain.

3. Other list operations are also simple:

```
#include "List.h"

void HashInsert(HashTable ht, Item it) {
   Key k = key(it);
   int i = hash(k, ht->N);
   ListInsert(ht->lists[i], it);
}
void HashDelete(HashTable ht, Key k) {
   int i = hash(k, ht->N);
   ListDelete(ht->lists[i], k);
}
```
[^2]

Cost analysis:
- N array entries (slots), M stored items
- average list length L = M/N
- best case: all lists are same length L
- worst case: one list of length M   (h(k)=0 )
- searching within a list of length n :
   - best: 1, worst: n, average: n/2  ⇒  O(n)
- if good hash and M≤N, cost is 1
- if good hash and M>N, cost is (M/N)/2

> Ratio of items/slots is called   load α = M/N

### Linear Probing
Collision resolution by finding a new location for ```Item```
- hash indicates slot i  which is already used
- try next slot, then next, until we find a free slot
- insert item into available slot

Examples:
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hash-collision/Pics/hash-linear.png)

1. Concrete data structures for hashing via linear probing:

```
typedef struct HashTabRep {
   Item **items; // array of pointers to Items
   int  N;       // # elements in array
   int  nitems;  // # items stored in HashTable
} HashTabRep;

HashTable newHashTable(int N)
{
   HashTabRep *new = malloc(sizeof(HashTabRep));
   assert(new != NULL);
   new->items = malloc(N*sizeof(Item *));
   assert(new->items != NULL);
   for (int i = 0; i < N; i++) new->items[i] = NULL;
   new->N = N; new->nitems = 0;
   return new;
}
```

2. Insert function for linear probing:
```
void HashInsert(HashTable ht, Item it)
{
   assert(ht->nitems < ht->N);
   int N = ht->N;
   Key k = key(it);
   Item **a = ht->items;
   int i = hash(k,N);
   for (int j = 0; j < N; j++) {
      if (a[i] == NULL) break;
      if (equal(k,key(*(a[i])))) break;
      i = (i+1) % N;
   }
   if (a[i] == NULL) ht->nitems++;
   if (a[i] != NULL) free(a[i]);
   a[i] = copy(it);
}
```

3. Search function for linear probing:
```
Item *HashGet(HashTable ht, Key k)
{
   int N = ht->N;
   Item **a = ht->items;
   int i = hash(k,N);
   for (int j = 0; j < N; j++) {
      if (a[i] == NULL) break;
      if (equal(k,key(*(a[i]))))
         return a[i];
      i = (i+1) % N;
   }
   return NULL;
}
```

Search cost analysis:
- cost to reach first Item is O(1)
- subsequent cost depends how much we need to scan
- affected by load α = M/N   (i.e. how "full" is the table)
- average cost for successful search = 0.5*(1 + 1/(1-α))
- average cost for unsuccessful search = 0.5*(1 + 1/(1-α)2)

> Example costs (assuming large table, e.g. N>100 ):
> load (α)	0.50  	0.67  	0.75  	0.90
> search hit	1.5	2.0	3.0	5.5
> search miss	2.5	5.0	8.5	55.5

> [^3]

Deletion slightly tricky for linear probing.

Need to ensure no NULL in middle of "probe path" (i.e. previously relocated items moved to appropriate location)

![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hash-collision/Pics/hash-probe-delete.png)

Delete function for linear probing:

```
void HashDelete(HashTable ht, Key k)
{
   int N = ht->N;
   Item *a = ht->items;
   int i = hash(k,N);
   for (int j = 0; j < N; j++) {
      if (a[i] == NULL) return; // k not in table
      if (equal(k,key(*(a[i])))) break;
      i = (i+1) % N;
   }
   free(a[i]);  a[i] = NULL;  ht->nitems--;
   // clean up probe path
   i = (i+1) % N;
   while (a[i] != NULL) {
      Item it = *(a[i]);
      a[i] = NULL;  // remove 'it'
      ht->nitems--;
      HashInsert(ht, it); // insert 'it' again
      i = (i+1) % N;
   }
}
```

Linear probing example:
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hash-collision/Pics/probing.png)

A problem with linear probing: clusters
- E.g. insert  5,  6,  15,  16,  14,  25,  with hash(k) = k%10
![Alt text](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/hash-collision/Pics/clustering.png)

### Double Hashing
Double hashing improves on linear probing:
- by using an increment which ...
   - is based on a secondary hash of the key
   - ensures that all elements are visited (can be ensured by using an increment which is relatively prime to N)
- tends to eliminate clusters ⇒ shorter probe paths

To generate relatively prime
- set table size to prime e.g. N=127
- ```hash2()``` in range [1..N1] where N1 < 127 and prime

1. Concrete data structures for hashing via double hashing:

```
typedef struct HashTabRep {
   Item **items; // array of pointers to Items
   int  N;       // # elements in array
   int  nitems;  // # items stored in HashTable
   int  nhash2;  // second hash mod
} HashTabRep;

#define hash2(k,N2) (((k)%N2)+1)

HashTable newHashTable(int N)
{
   HashTabRep *new = malloc(sizeof(HashTabRep));
   assert(new != NULL);
   new->items = malloc(N*sizeof(Item *));
   assert(new->items != NULL);
   for (int i = 0; i < N; i++)
      new->items[i] = NULL;
   new->N = N; new->nitems = 0;
   new->nhash2 = findSuitablePrime(N);
   return new;
}
```

2. Search function for double hashing:
```
Item *HashGet(HashTable ht, Key k)
{
   Item **a = ht->items;
   int N = ht->N;
   int i = hash(k,N);
   int incr = hash2(k,ht->nhash2);
   for (int j = 0, j < N; j++) {
      if (a[i] == NULL) break;  // k not found
      if (equal(k,key(*(a[i]))) return a[i];
      i = (i+incr) % N;
   }
   return NULL;
}
```

3. Insert function for double hashing:
```
void HashInsert(HashTable ht, Item it)
{
   assert(ht->nitems < ht->N); // table full
   Item **a = ht->items;
   Key k = key(it);
   int N = ht->N;
   int i = hash(k,N);
   int incr = hash2(k,ht->nhash2);
   for (int j = 0, j < N; j++) {
      if (a[i] == NULL) break;
      if (equal(k,key(*(a[i])))) break;
      i = (i+incr) % N;
   }
   if (a[i] == NULL) ht->nitems++;
   if (a[i] != NULL) free(a[i]);
   a[i] = copy(it);
}
```

Search cost analysis:
- cost to reach first Item is O(1)
- subsequent cost depends how much we need to scan
- affected by  load α = M/N   (i.e. how "full" is the table)
- average cost for successful search $\frac{1}{\alpha} ln(\frac{1}{1 - \alpha})$
- average cost for unsuccessful search = $\frac{1}{1 - \alpha}.$

Costs for double hashing (assuming large table, e.g. N>100 ):
load (α)	0.5  	0.67  	0.75  	0.90
search hit	1.4	1.6	1.8	2.6
search miss	1.5	2.0	3.0	5.5
Can be significantly better than linear probing
- especially if table is heavily loaded

### Hashing Summary
Collision resolution approaches:
- chaining: easy to implement, allows α > 1
- linear probing: fast if α << 1, complex deletion
- double hashing: faster than linear probing, esp for α ≅ 1

Only chaining allows α > 1, but performance poor when α  1

For arrays, once M  exceeds initial choice of N,
- need to expand size of array (N)
- problem: hash function relies on N, so changing array size potentially requires rebuiling whole table
- dynamic hashing methods exist to avoid this


#
[^1]: in slide 17 week 9 under give topic (for a Priority Queue containing N items)
[^2]: Essentially: select a list; operate on that list.
[^3]: Assumes reasonably uniform data and good hash function.
