# First Lecture
## Sorting
### Sorting

Sorting involves arranging a collection of items in order

- based on some property of the items (e.g. key)
- using an ordering relation on that property

Why is sorting useful?
- speeds up subsequent searching
- arranges data in a human-useful way (e.g. list of students in a tute class, ordered by family-name or id)
- arranges data in a computationally-useful way (e.g. duplicate detection/removal, many DBMS operations)

Sorting occurs in many data contexts, e.g.
- arrays, linked-lists   (internal, in-memory)
- files   (external, on-disk)

Different contexts generally require different approaches
- and sorting has been well-studied over the last 50 years

Our view of the sorting problem:
- arrange an array of Items in ascending order
- could sort whole array, or could sort a slice of the array

### The Sorting Problem

Arrange items in array slice ```a[lo..hi]``` into sorted order:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sorting/Pics/sorting.png)

For ```Item a[N]```,  frequently ```(lo == 0), (hi == N-1)```

More formally ...

Precondition:
- ```lo,hi``` are valid indexes, i.e. ```0 ≤ lo < hi ≤ N-1```
- ```a[lo..hi]``` contains defined values of type ```Item```

Postcondition:
- ```a[lo..hi]``` contains same set (bag) of values
- foreach ```i``` in ````lo..hi-1,  a[i] ≤ a[i+1]```

We sort arrays of ```Items```, which could be
- simple values, e.g.  ```int,  char,  float```
- structured values, e.g. ```struct```

Each ```Item``` contains a ```key,``` which could be
- a simple value, or a collection of values

> The order of ```key``` values determines the order of the sort.
> Duplicate ```key``` values are not precluded.
> In our discussions, we often use the ```key``` value as if it is the whole ```Item```

Properties of sorting algorithms: stable, adaptive

Stable sort:
- let  ```x = a[i],  y = a[j],  key(x) == key(y)```
- "precedes" = occurs earlier in the array (smaller index)
- if x precedes y in ```a```, then x precedes y in sorted ```a```

Adaptive:
- behaviour/performance of algorithm affected by data values
- i.e. best/average/worst case performance differs

In analysing sorting algorithms:
- N = number of items = ```hi-lo+1```
- C = number of comparisons between items
- S = number of times items are swapped

> Aim to minimise C and S

Cases to consider for initial order of items:
- random order: ```Items``` in ```a[lo..hi]``` have no ordering
- sorted order:  ```a[lo]  ≤  a[lo+1]  ≤  ...  ≤  a[hi]```
- revserse order:  ```a[lo]  ≥  a[lo+1]  ≥  ...  ≥  a[hi]```

### Comparison of Sorting Algorithms

A variety of sorting algorithms exist
- most are in-memory algorithms, some also work with files
- two major classes:   O(n2), O(n log n)
- O($n^2$) are acceptable if n is small (hundreds)

> Ways to compare algorithms:
> - implement and monitor performance
> - graphic visualisations
> - or even folk dancing

### Implementing Sorting 

- Concrete framework:
```
// we deal with generic Items
typedef SomeType Item;

// abstractions to hide details of Items
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define swap(A,B) {Item t; t = A; A = B; B = t;}

// Sorts a slice of an array of Items, a[lo..hi]
void sort(Item a[], int lo, int hi);

// Check for sortedness (to validate functions)
int isSorted(Item a[], int lo, int hi);
```

### Implementing ```isSorted()```

Implementation of the ```isSorted()``` check.
```
bool isSorted(Item a[], int lo, int hi)
{
   for (int i = lo; i < hi; i++) {
      if (!less(a[i],a[i+1])) return false;
   }
   return true;
}
```
- Checks pairs  ```(a[lo],a[lo+1]), ... (a[hi-1],a[hi])```
- Check whole array  ```Item a[N]```  via  ```isSorted(a, 0, N-1)```

### Sorts on Linux

The ```sort``` command
- sorts a file of text, understands fields in line
- can sort alphabetically, numerically, reverse, random

The ```qsort()``` function
- ```qsort(void *a, int n, int size, int (*cmp)())```
- sorts any kind of array   (n objects, each of ```size``` bytes)
- requires the user to supply a comparison function   (e.g. ```strcmp()```)
- sorts list of items using the order given by ```cmp()```

> Note: the comparison function is passed as a parameter; discussed elsewhere.

### Describing Sorting Algorithms
To describe sorting, we use diagrams like:

![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sorting/Pics/showing-sorting.png)

In these algorithms ...
- some part(s) of the array is already sorted
- each iteration makes more of the array sorted
> Note. also see animations [^1]

## O(n^2) Sorting Algorithms
### O(n^2) Sorting Algorithms
One class of sorting methods has complexity O(n2)
- selection sort ... simple, non-adaptive sort
- bubble sort ... simple, adaptive sort
- insertion sort ... simple, adaptive sort
- shellsort ... improved version of insertion sort

> There are sorting methods with better complexity O(n log n)
> But for small arrays, the above methods are adequate
> <br>


### Selection Sort

Simple, non-adaptive method:
- find the smallest element, put it into first array slot
- find second smallest element, put it into second array slot
- repeat until all elements are in correct position

"Put in xth array slot" is accomplished by:
- swapping value in xth position with xth smallest value
> Each iteration improves "sortedness" by one element

State of array after each iteration:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sort-simple/Pics/sel-sort.png)

1. C function for Selection sort:
```
void selectionSort(int a[], int lo, int hi)
{
   int i, j, min;
   for (i = lo; i <= hi-1; i++) {
      min = i;
      for (j = i+1; j <= hi; j++) {
         if (less(a[j],a[min])) min = j;
      }
      swap(a[i], a[min]);
   }
}
```

Cost analysis (where n = ```hi-lo+1```):
- on first pass, n-1 comparisons, 1 swap
- on second pass, n-2 comparisons, 1 swap
- ... on last pass, 1 comparison, 1 swap
- C = (n-1)+(n-2)+...+1 = n*(n-1)/2 = (n2-n)/2 ⇒ O(n2)
- S = n-1

> Cost is same, regardless of sortedness of original array.

### Bubble Sort

Simple adaptive method:
- make multiple passes from N to i (i=0..N-1)
- on each pass, swap any out-of-order adjacent pairs
- elements move until they meet a smaller element
- eventually smallest element moves to i th position
- repeat until all elements have moved to appropriate position
- stop if there are no swaps during one pass (already sorted)

![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sort-simple/Pics/bubbles.png)

State of array after each iteration:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sort-simple/Pics/bub0-sort.png)

- Bubble sort example  (from Sedgewick):
```
S O R T E X A M P L E
A S O R T E X E M P L
A E S O R T E X L M P
A E E S O R T L X M P
A E E L S O R T M X P
A E E L M S O R T P X
A E E L M O S P R T X
A E E L M O P S R T X
A E E L M O P R S T X
... no swaps ⇒ done ...
A E E L M O P R S T X
```

- C function for Bubble Sort:
```
void bubbleSort(int a[], int lo, int hi)
{
   int i, j, nswaps;
   for (i = lo; i < hi; i++) {
      nswaps = 0;
      for (j = hi; j > i; j--) {
         if (less(a[j], a[j-1])) {
            swap(a[j], a[j-1]);
            nswaps++;
         }
      }
      if (nswaps == 0) break;
   }
}
```

Cost analysis (where n = hi-lo+1):
- cost for i th iteration:
  - n-i comparisons, ?? swaps
  - S depends on "sortedness", best=0, worst=n-i
- how many iterations? depends on data orderedness
  - best case: 1 iteration,   worst case: n-1 iterations
- Costbest = n   (data already sorted)
- Costworst = n-1 + ... + 1   (reverse sorted)
- Complexity is thus O($n^2$)

### Insertion Sort

Simple adaptive method:
- take first element and treat as sorted array (length 1)
- take next element and insert into sorted part of array
- so that order is preserved
- above increases length of sorted part by one
- repeat until whole array is sorted

![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sort-simple/Pics/ins-sort.png)

- Insertion sort example  (from Sedgewick):
```
S O R T E X A M P L E
S O R T E X A M P L E
O S R T E X A M P L E
O R S T E X A M P L E
O R S T E X A M P L E
E O R S T X A M P L E
E O R S T X A M P L E
A E O R S T X M P L E
A E M O R S T X P L E
A E M O P R S T X L E
A E L M O P R S T X E
A E E L M O P R S T X
```

- C function for insertion sort:
```
void insertionSort(int a[], int lo, int hi)
{
   int i, j, val;
   for (i = lo+1; i <= hi; i++) {
      val = a[i];
      for (j = i; j > lo; j--) {
         if (!less(val,a[j-1])) break;
         a[j] = a[j-1];
      }
      a[j] = val;
   }
}
```

Cost analysis (where n = hi-lo+1):
- cost for inserting element into sorted list of length i
  - C=??, depends on "sortedness", best=1, worst=i
  - S=??, don't swap, just shift, but do C-1 shifts
- always have n iterations
- Costbest = 1 + 1 + ... + 1   (already sorted)
- Costworst = 1 + 2 + ... + n = n*(n+1)/2   (reverse sorted)
- Complexity is thus O(n2)

### ShellSort: Improving Insertion Sort

Insertion sort:
- based on exchanges that only involve adjacent items
- already improved above by using moves rather than swaps
- "long distance" moves may be more efficient

Shellsort: basic idea
- array is h-sorted if taking every h'th element yields a sorted array
- an h-sorted array is made up of n/h interleaved sorted arrays
- Shellsort: h-sort array for progressively smaller h, ending with 1-sorted

Example h-sorted arrays:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/sort-simple/Pics/h-sorted.png)


```
void shellSort(int a[], int lo, int hi)
{
   int hvals[8] = {701, 301, 132, 57, 23, 10, 4, 1};
   int g, h, start, i, j, val;
   for (g = 0; g < 8; g++) {
      h = hvals[g];
      start = lo + h;
      for (i = start; i <= hi; i++) {
         val = a[i];
         for (j = i; j >= start; j -= h) {
            if (!less(val,a[j-h]) break;
            a[j] = a[j-h];
         }
         a[j] = val;
      }
   }
}
```

Effective sequences of h values have been determined empirically.

E.g. hi+i = 3hi+1 ... 1093, 364, 121, 40, 13, 4, 1

Efficiency of Shellsort:
- depends on the sequence of h values
- suprisingly, Shellsort has not yet been fully analysed
- above sequence has been shown to be O(n^(3/2))
- others have found sequences which are O(n^(4/3))

### Summary of Elementary Sorts
Comparison of sorting algorithms  (animated comparison) [table in slide 21/22 in O(n^2) sorts]

The best depends upon:
- depends on cost of compare vs swap vs move for ```Item```s
- depends on likelihood of average vs worst case

### Sorted Linked Lists

Selection sort on linked lists
- L = original list, S = sorted list (initially empty)
- find largest value V in L; unlink it
- link V node at front of S

Bubble sort on linked lists
- traverse list: if current > next, swap node values
- repeat until no swaps required in one traversal

Selection sort on linked lists
- L = original list, S = sorted list (initially empty)
- scan list L from start to finish
- insert each item into S in order 

## Quicksort
### Quicksort
Previous sorts were all  O(nk)   (where k>1).

We can do better ...

Quicksort: basic idea
- choose an item to be a "pivot"
- re-arrange (partition) the array so that
  - all elements to left of pivot are smaller than pivot
  - all elements to right of pivot are greater than pivot
- (recursively) sort each of the partitions

Phases of quicksort:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/quicksort/Pics/qsort-alg.png)

### Quicksort Implementation

1. Elegant recursive solution ...
```
void quicksort(Item a[], int lo, int hi)
{
   int i; // index of pivot
   if (hi <= lo) return;
   i = partition(a, lo, hi);
   quicksort(a, lo, i-1);
   quicksort(a, i+1, hi);
}
```

2. Partitioning phase:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/quicksort/Pics/partitioning.png)

Partition implementation:
```
int partition(Item a[], int lo, int hi)
{
   Item v = a[lo];  // pivot
   int  i = lo+1, j = hi;
   for (;;) {
      while (less(a[i],v) && i < j) i++;
      while (less(v,a[j]) && j > i) j--;
      if (i == j) break;
      swap(a,i,j);
   }
   j = less(a[i],v) ? i : i-1;
   swap(a,lo,j);
   return j;
}
```

### Quicksort Performance

Best case: O(nlogn) comparisons
- choice of pivot gives two equal-sized partitions
- same happens at every recursive level
- each "level" requires approx n comparisons
- halving at each level ⇒ log2n levels

Worst case: O(n2) comparisons
- always choose lowest/highest value for pivot
- partitions are size 1 and n-1
- each "level" requires approx n comparisons
- partitioning to 1 and n-1 ⇒ n levels

### Quicksort Improvements

Choice of pivot can have significant effect:
- always choosing largest/smallest ⇒ worst case
- try to find "intermediate" value by median-of-three

![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/quicksort/Pics/median3.png)

Median-of-three partitioning:
```
void medianOfThree(Item a[], int lo, int hi)
{
   int mid = (lo+hi)/2;
   if (less(a[mid],a[lo])) swap(a, lo, mid);
   if (less(a[hi],a[mid])) swap(a, mid, hi);
   if (less(a[mid],a[lo])) swap(a, lo, mid);
   // now, we have a[lo] < a[mid] < a[hi]
   // swap a[mid] to a[lo+1] to use as pivot
   swap(a, mid, lo+1);
}
void quicksort(Item a[], int lo, int hi)
{
   if (hi <= lo) return;
   medianOfThree(a, lo, hi);
   int i = partition(a, lo+1, hi-1);
   quicksort(a, lo, i-1);
   quicksort(a, i+1, hi);
}
```

Another source of inefficiency:
- pushing recursion down to very small partitions
- overhead in recursive function calls
- little benefit from partitioning when size < 5

Solution: handle small partitions differently
- switch to insertion sort on small partitions, or
- don't sort yet; use post-quicksort insertion sort

Quicksort with thresholding ...
```
void quicksort(Item a[], int lo, int hi)
{
   if (hi-lo < Threshhold) {
      insertionSort(a, lo, hi);
      return;
   }
   medianOfThree(a, lo, hi);
   int i = partition(a, lo+1, hi-1);
   quicksort(a, lo, i-1);
   quicksort(a, i+1, hi);
}
```

If the array contains many duplicate keys
- standard partitioning does not exploit this
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/quicksort/Pics/partition2.png)

- can improve performance via three-way partitioning
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/quicksort/Pics/partition3.png)

Bentley/McIlroy approach to three-way partition:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/quicksort/Pics/partitioning3.png)

### Non-recursive Quicksort
Quicksort can be implemented using an explicit stack:
```
void quicksortStack (Item a[], int lo, int hi)
{
   Stack s = newStack();
   StackPush(s,hi); StackPush(s,lo);
   while (!StackEmpty(s)) {
      lo = StackPop(s);
      hi = StackPop(s);
      if (hi > lo) { 
         int i = partition (a,lo,hi);
         StackPush(s,hi); StackPush(s,i+1);
         StackPush(s,i-1); StackPush(s,lo);
      }
   }
}
```


#
[^1]: https://www.toptal.com/developers/sorting-algorithms