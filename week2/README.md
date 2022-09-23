# <b> Second Week </b>
# <b> First lecture </b>
## <b> Continuing from Recursion </b>
#

- Deleting from list using Recursion:
```
struct node *deleteR (struct node *list, int value) {
  if (list == NULL) {
    fprintf(stderr, "warning: value %d is not in list\n");
  } else if (list->data == value) {
    struct node *tmp = list;
    list = list->next; // remove first item
    free(tmp);         // free the value
  } else {
    list->next = deleteR(list->next, value);  // recursive call to deleteR function with the next address of the list
  }
  return list;
}
```

- Print Python List using Recursion:
```
// print contents of list in Python Syntax

void print_list(struct node *head) {
  printf("[");
  if (head != NULL) {
    print_list_items(head); 
  }
  printf("]");
}

// recursive function
void print_list_items(struct node *head) {
  printf("%d", head->data);
  if (head->next != NULL) {
    printf(", ");
    // recursive call
    print_list_items(head->next);
  }
}
```

## <b> Analysis of Algorithms </b>
#
### <b> Binary Search </b>
#
- For example, search for 61; number of elements N = 16.

Assumptions (finding 61 in an ordered list example):
1. Seach for 61, size ~  N/2 (directly go to middle part; determine if it is in the right hand side or left hand side of the middle or if it is the exact middle)
2. Search for 61, size ~ N/4 (going to half of half; repeat the brackets above)
3. Search for 61, size ~ N/8 (going to half of half of half; repeat brackets above)

- General Pattern = N/2^k [^1]
- This is the basis of binary search.


Search by ascending order of time taken to search:
1. log(n)
2. n
3. n log(n)
4. n^2
5. n^3
6. 2^n (exponential)

- it is wise to prioritise readability over performance when it comes to an algorithm (as readable code make it easier to read stuff)

### <b>Running Time </b>
# 
An algorithm is a step-by-step procedure
- for solving a problem
- in a finite amount of time

Most algorithms map input to output
- running time typically grows with input size
- average time often difficult to determine (amount of time CPU takes to process, etc)
- Focus on worst case running time
  - easier to analyse
  - crucial to many applications: finance, robotics, games, etc.

### <b> Empirical Analysis </b>
#
Process:
1. Write program that implements an algorithm
2. Run program with inputs of varying size and composition
3. Measure the actual running time
4. Plot the results

- not simple all the time

Limitations to empirical analysis
- requires to implement the algorithm, which may be difficult
- results may not be indicative of running time on other inputs
- same hardware and operating system must be used in order to compare two algorithms

### <b>Theoretical Analysis </b>
#
- Uses high-level description of the algorithm instead of implementation ("pseudocode")
- Characterises running time as a function of the input size, n
- Takes into account all possible inputs
- Allows us to evaluate the speed of an algorithm independent of the hardware/software environment

### <b> Pseudocode </b>
#
- useful if you don't know how to implement; write algorithm and then implement
- More structured than English prose
- Less detailed than a program
- Preferred notation for describing algorithms
- Hides program design issues

Example:
Find maximal element in an array
```
arrayMax(A):
    Input array A of n integers
    Output maximum element of A

    currentMax = A[0]
    for all i = 1..n-1 do
        if A[i] > currentMax then
            currentMax = A[i]
        end if
    end for
    return currentMax    
```

### <b> Primitive Operations </b>
#
(like assigning a value and compare; etc)
- Basic computations performed by an algorithm
- Identifiable in pseudocode
- Largely independent of the programming language
- Exact definition not important   (we will shortly see why)
- Assumed to take a constant amount of time in the RAM model

Examples:
- evaluating an expression
- indexing into an array
- calling/returning from a function

- good to write algorithms as pseudocode


Counting primitive operations in the previous example:
```
arrayMax(A):
    Input array A of n integers
    Output maximum element of A

    currentMax = A[0]                // [1]
    for all i = 1..n-1 do
        if A[i] > currentMax then    // [n + (n - 1)]
            currentMax = A[i]        // [2(n - 1)]
        end if
    end for
    return currentMax                // [1]

    Total = 5n - 2
```
- 2n - 1 is the number of operations in [n + (n - 1)]
  - 1 to n - 1; how  many increments needed?
  - therefore, n and n - 1 is the number of increments
  
- compare and check at [2(n - 1)]
  - since it is comaring; it is repeating (n - 1) twice

- [n - 1] is max number of changes (estimating to worst case scenario)
[^2]

### <b> Estimating Run Times </b>
#
From previous example; 

- Algorithm arrayMax requires 5n – 2 primitive operations in the worst case

- best case requires 4n – 1 operations   (why?)
- Define:
  - a … time taken by the fastest primitive operation
  - b … time taken by the slowest primitive operation
- Let T(n) be worst-case time of arrayMax. Then
   - a·(5n - 2) ≤ T(n) ≤ b·(5n - 2)

- Hence, the running time T(n) is bound by two linear functions

- Seven commonly encountered functions for algorithm analysis are as follows:
1. Constant ≅ 1
2. Logarithmic ≅ log n (binary search)
3. Linear ≅ n
4. N-Log-N ≅ n log n
5. Quadratic ≅ n2
6. Cubic ≅ n3
7. Exponential ≅ 2n

- The growth rate is not affected by constant factors or lower-order terms
- Examples:
  - $10^2 n$ + $10^5$ is a linear function
  - $10^5n^2$ + $10^8n$ is a quadratic function
- actual value increases, but the rate does not change

Example:
Estimate running time: 
```
matrixProduct(A,B):
   Input  n×n matrices A, B
   Output n×n matrix A·B
 
   for all i=1..n do               // 2n+1 (O(n))
    for all j=1..n do              // n(2n+1) (n*O(n))
        C[i,j]=0                   // n2
        for all k=1..n do          // n2(2n+1)
            C[i,j]=C[i,j]+A[i,k]·B[kj]                   //n3·5
        end for
      end for
   end for
   return C                        // 1

```
- Total = 7$n^3$ + 4$n^2$ + 3n + 2

### <b> Big-Oh notation </b>
#
- Given functions f(n) and g(n), we say that

- f(n) is O(g(n))
- if there are positive constants c and n0 such that

- f(n) ≤ c·g(n)    ∀n ≥ n0


### <b> To find the Big - O function (recursion) </b>
#

Example: function 2n + 10 is $O(n)$
- 2n + 10 <= c.n
  => (c - 2)n >= 10
  => n >= 10/(c - 2)

- pick c and n from graph

Example; n^2 is not O(n)
- n^2 <= c*n
  => n <= c
  -> eventually escapes; therefore it has no O(n) function


Exercise:

Q. Show that $\sum_{i=1}^{n}i$ is O($n^2$)

A. 
- 1 + 2 + 3 + 4 + ... + (n - 1) + n
- (n * (n + 1))/ 2
- $(n^2 + n)/2$
- $n^2/2 + n/2$ (ignore constants and ignore n)
- O($n^2$)

### <b> Asymptotic Analysis of Algorithms </b>
#
Asymptotic analysis of algorithms determines running time in big-Oh notation:
- find worst-case number of primitive operations as a function of input size
- express this function using big-Oh notation

Example:
- algorithm arrayMax executes at most 5n – 2 primitive operations 
  - algorithm arrayMax "runs in O(n) time"


- Constant factors and lower-order terms eventually dropped 
  - can disregard them when counting primitive operations


Example: Computing prefix averages
- The i-th prefix average of an array X is the average of the first i elements:
$A[i] = (X[0] + X[1] + … + X[i]) / (i+1)$

- A quadratic alogrithm to compute prefix averages:

```
prefixAverages1(X):
|  Input  array X of n integers
|  Output array A of prefix averages of X
|
|  for all i=0..n-1 do          // O(n)
|  |  s=X[0]                    // O(n)
|  |  for all j=1..i do         // O(n2)
|  |     s=s+X[j]               // O(n2)
|  |  end for
|  |  A[i]=s/(i+1)              // O(n)
|  end for
|  return A     // O(1)

```                    
- 2·O($n^2$) + 3·O(n) + O(1) = O($n^2$)
- Time complexity of algorithm prefixAverages1 is O($n^2$)

or if you have another algorithm;

- The following algorithm computes prefix averages by keeping a running sum:

```
prefixAverages2(X):
|  Input  array X of n integers
|  Output array A of prefix averages of X
|
|  s=0
|  for all i=0..n-1 do          // O(n)
|     s=s+X[i]                  // O(n)
|     A[i]=s/(i+1)              // O(n)
|  end for
|  return A                     // O(1)
```
- Thus, prefixAverages2 is O(n)
- another example would be binary search (in slides 35 - 43 in Analysis of Algorithms)
    - basically need to see size reduction

### <b> Relatives of Big-Oh </b>
#
1. big-Omega

- f(n) is Ω(g(n)) if there is a constant c > 0 and an integer constant n0 ≥ 1 such that
- f(n) ≥ c·g(n)    ∀n ≥ n0

2. big-Theta

- f(n) is Θ(g(n)) if there are constants c',c'' > 0 and an integer constant n0 ≥ 1 such that
- c'·g(n) ≤ f(n) ≤ c''·g(n)    ∀n ≥ n0

Categories: 
- f(n) is O(g(n)) if f(n) is asymptotically less than or equal to g(n)
- f(n) is Ω(g(n)) if f(n) is asymptotically greater than or equal to g(n)
- f(n) is Θ(g(n)) if f(n) is asymptotically equal to g(n)

- Examples:

  - ¼n2 is Ω(n2)
    - need c > 0 and n0 ≥ 1 such that ¼n2 ≥ c·n2 for n≥n0
    - let c=¼ and n0=1
  - ¼n2 is Ω(n)
    - need c > 0 and n0 ≥ 1 such that ¼n2 ≥ c·n for n≥n0
    - let c=1 and n0=2
  - ¼n2 is Θ(n2)
    - since ¼n2 is in Ω(n2) and O(n2)


### <b> Complexity Classes </b>
#
Problems in Computer Science …

  - some have polynomial worst-case performance (e.g. n2)
  - some have exponential worst-case performance (e.g. 2n)

Classes of problems:
  - P = problems for which an algorithm can compute answer in polynomial time
  - NP = includes problems for which no P algorithm is known [^3]

Computer Science jargon for difficulty:

- tractable … have a polynomial-time algorithm (useful in practice)
- intractable … no tractable algorithm is known (feasible only for small n)
- non-computable … no algorithm can exist
[^4]

### <b> General and Test Algorithms </b>
#
In scenarios where

- it is simple to test whether a given state is a solution
- it is easy to generate new states   (preferably likely solutions)

then a generate and test strategy can be used.

It is necessary that states are generated systematically
- so that we are guaranteed to find a solution, or know that none exists
  - some randomised algorithms do not require this, however. 
  (more on this later in this course)

Simple example: checking whether an integer n is prime

- generate/test all possible factors of n
- if none of them pass the test  ⇒ n is prime

Generation is straightforward:
- produce a sequence of all numbers from 2 to n-1

Testing is also straightfoward:
- check whether next number divides n exactly

# Second Lecture
### Continuation of Generate and Test Algorithms
#
Example:
```
isPrime(n):
  Input  natural number n
  Output true if n prime, false otherwise

  for all i=2..n-1 do      // generate
    if n mod i = 0 then   // test
     return false       // i is a divisor => n is not prime
    end if
  end for
  return true              // no divisor => n is prime
```
- complexity of isPrime is O(n)
- can be optimised: check only numbers between 2 and $\lfloor \sqrt{n} \rfloor \to O(\sqrt{n})$.

<u>Example:</u>
<br>
<br>
Q. Is there a subset S of these numbers with sum(S) = 1000?
```
34,  38,  39,  43,  55,  66,  67,  84,  85,  91,
101, 117, 128, 138, 165, 168, 169, 182, 184, 186,
234, 238, 241, 276, 279, 288, 386, 387, 388, 389
```
<u>General problem:</u>
- given n integers and a target sum k
- is there a subset that adds up to exactly k?

<u> Generate and test approach: </u>

```
// Pseudocode 

subsetsum(A,k):
  Input  set A of n integers, target sum k

  Output true if $Σ_(b∈B)b = k$ for some B ⊆ A
      false otherwise

  for each subset S⊆A do
    if sum(S)=k then
       return true
    end if
  end for
  return false
```

1. How many subsets are there of n elements?
2. How could we generate them?

Given: a set of n distinct integers in an array A …

- produce all subsets of these integers
A method to generate subsets:
- represent sets as n bits   (e.g. n=4, 0000, 0011, 1111 etc.)
- bit i represents the i th input number
- if bit i is set to 1, then A[i] is in the subset
- if bit i is set to 0, then A[i] is not in the subset
- e.g. if $A[\text{ }] == \{1,2,3,5\}$ then $0011$ represents $\{1,2\}$

<u> Algorithm </u>

```
subsetsum1(A,k):
  Input  set A of n integers, target sum k
  Output true if Σb∈Bb=k for some B⊆A
         false otherwise

  for s=0..2n-1 do
   if k = Σ(ith bit of s is 1) A[i] then
       return true
    end if
  end for
  return false
```

- Obviously, subsetsum1 is $O(2n)$.

Alternative approach
<br>

<b> subsetsum2(A,n,k) </b>

(returns true if any subset of A[0..n-1] sums to k; returns false otherwise)

- if the nth value A[n-1] is part of a solution …
then the first n-1 values must sum to k – A[n-1]
- if the nth value is not part of a solution …
then the first n-1 values must sum to k
- base cases: k=0 (solved by {}); n=0 (unsolvable if k>0)

```
subsetsum2(A,n,k):
  Input  array A, index n, target sum k
  Output true if some subset of A[0..n-1] sums up to k
         false otherwise

  if k=0 then
     return true   // empty set solves this
  else if n=0 then
     return false  // no elements => no sums
  else
     return subsetsum2(A,n-1,k-A[n-1]) ∨ subsetsum2(A,n-1,k)
  end if
```

<u>Cost analysis: </u>

- $C_i$ = #calls to subsetsum2() for array of length i
- for best case, $C_n = C_{n-1}$    (why?)
- for worst case, $Cn = 2·C_{n-1} \to C_n = 2n$

Thus, subsetsum2 also is $O(2n)$.

- Subset Sum is typical member of the class of NP-complete problems

- intractable … only algorithms with exponential performance are known
  - increase input size by 1, double the execution time
  - increase input size by 100, it takes 2100 = 1,267,650,600,228,229,401,496,703,205,376 times as long to execute
- but if you can find a polynomial algorithm for Subset Sum, 
  then any other NP-complete problem becomes P !

## <b>ADTs (Abstract Data Types)</b>
#
### Abstract Data Types
#
A data type is ...

- a set of values   (atomic or structured values)
- a collection of operations on those values

An abstract data type is ... [^5]
- an approach to implementing data types
- separates interface from implementation [^6]
- users of the ADT see only the interface
- builders of the ADT provide an implementation
<br>
<br>
> E.g. do you know what a $(FILE *)$ looks like? do you want/need to know?

### DTs, ADTs, GADTs
#
We want to distinguish ...

1. DT = (non-abstract) data type   (e.g. C strings)
  - internals of data structures are visible   (e.g. char s[10];)

2. ADT = abstract data type   (e.g. C files)
- can have multiple instances   (e.g. Set a, b, c;)

3. GADT = generic (polymorphic) 

- abstract data type
- can have multiple instances   (e.g. Set $\text{<int>}$ a, b, c;)
- can have multiple types   (e.g. Set $\text{<int>}$ a; Set $\text{<char>}$ b;)
- not available natively in the C language

### Interface/ Implementation
#
ADT interface provides: (.h file)
- a user-view of the data structure (e.g. FILE*)
- function signatures (prototypes) for all operations
- semantics of operations (via documentation)
- a contract between ADT and its clients

ADT implementation gives (.c file)
- concrete definition of the data structures
- definition of functions for all operations

### Collections
#
Many of the ADTs we deal with ...

- consist of a collection of items
- where each item may be a simple type or an ADT
- and items often have a key (to identify them)

Collections may be categorised by ...
- structure:   linear (list), branching (tree), cyclic (graph)
- usage:   set, matrix, stack, queue, search-tree, dictionary, ...

### Collection Structures
#
(draws in slide 5-8/30 in ADTs)
- linear, cyclic or binary trees

### Collections (cont.)
#
Typical operations on collections

- create an empty collection
- insert one item into the collection
- remove one item from the collection
- find an item in the collection
- check properties of the collection (size,empty?)
- drop the entire collection
- display the collection

### Example Set ADT
#
Set data type: collection of unique integer values.

"Book-keeping" operations:

```
Set newSet()  // create new empty set
void dropSet(Set) // free memory used by set
void showSet(Set) // display as {1,2,3...}
```

Assignment operations:

```
void readSet(FILE*,Set) // read+insert set values
Set SetCopy(Set) // make a copy of 
```

Data-type operations:

- ```void SetInsert (Set,int)``` ... add number into set
- ```void SetDelete(Set,int)``` ... remove number from set
- ```int SetMember(Set,int)``` ... set membership test
- ```Set SetUnion(Set,Set)``` ... union
- ```Set SetIntersect(Set,Set)``` ... intersection
- ```int SetCard(Set)``` ... cardinality (#elements)

> Note: union and intersection return a newly-created ```Set```

### Set ADT interface 
#
> (also in the Set ADT from lectureCode(2) folder)

```
// Set.h ... interface to Set ADT

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdbool.h>

typedef struct SetRep *Set;

Set newSet();              // create new empty set
void dropSet(Set);         // free memory used by set
Set SetCopy(Set);          // make a copy of a set
void SetInsert(Set,int);   // add value into set
void SetDelete(Set,int);   // remove value from set
bool SetMember(Set,int);   // set membership
Set SetUnion(Set,Set);     // union
Set SetIntersect(Set,Set); // intersection
int SetCard(Set);          // cardinality
void showSet(Set);         // display set on stdout
void readSet(FILE *, Set); // read+insert set values

#endif
```

1. Example set client: set of small odd numbers 

```
#include "Set.h"
...
Set s = newSet();

for (int i = 1; i < 26; i += 2)
    SetInsert(s,i);

showSet(s); 
putchar('\n');
```

Outputs:
```
{1,3,5,7,9,11,13,15,17,19,21,23,25}
```

2. Example: eliminating duplicates 

```
#include "Set.h"
...
// scan a list of items in a file
int item;
Set seenItems = newSet();
FILE *in = fopen(FileName,"r");
while (fscanf(in, "%d", &item) == 1) {
   if (!SetMember(seenItems, item)) {
      SetInsert(seenItems, item);
      process item;
   }
}
fclose(in);
```

### Set ADT Pre/Post conditions

Each ```Set``` operation has well-defined semantics.

Express these semantics in detail via statements of:
- what conditions need to hold at start of function
- what will hold at end of function (assuming successful)

Could  implement condition-checking via  ```assert() ```s

But only during the development/testing phase

- ```assert()``` does not provide useful error-handling

At the very least, implement as comments at start of functions.

If x is a variable of type T, where T is an ADT
  - $ptr(x)$ is the pointer stored in x
  - $val(x)$ is the abstract value represented by *x
  - $valid(T, x)$ indicates that
    - the collection of values in *x  satisfies all constraints on "correct" values of type T
  - $x'$ is the updated version of $x$ [^7]
  - $res$ value returned by a function
Can also use math/logic notation as used in pseudocode.


3. Examples of defining pre-/post conditions

```
// pre:  true
// post: valid(Set,res) and res = {}
Set newSet() { ... }

// pre:  valid(Set,s) and valid(int n)
// post: n ?? s'
void SetInsert(Set s, int n) { ... }

// pre:  valid(Set,s1) and valid(Set,s2)
// post: ?? n ?? res, n ?? s1 or n ?? s2
Set SetUnion(Set s1, Set s2) { ... }

// pre:  valid(Set,s)
// post: res = |s|
int SetCard(Set s)  { ... }
```
### Sets as Unsorted Arrays
#
[concrete data structure in slide 18/30]

1. Concrete data structure (in C):

```
#define MAXELEMS 1000

// concrete data structure
struct SetRep {
    int elems[MAXELEMS];
    int nelems;
};
```

- Need to set upper bound on number of elements
- Could do statically (as above) or dynamically
```
Set newSet(int maxElems) { .
```

2. Set creation:

```
// create new empty set
Set newSet()
{
   Set s = malloc(sizeof(struct SetRep));
   if (s == NULL) {
      fprintf(stderr, "Insufficient memory\n");
      exit(EXIT_FAILURE);
   }
   s->nelems = 0;
   // assert(isValid(s));
   return s;
}
```

3. Checking membership:

```
// set membership test
int SetMember(Set s, int n)
{   
   // assert(isValid(s));
   int i; 
   for (i = 0; i < s->nelems; i++)
      if (s->elems[i] == n) return TRUE;
   return FALSE;
}
```

4. Costs for set operations on unsorted array:

- card: read from struct;   constant cost   $O(1)$
- member: scan list from start;   linear cost   $O(n)$
- insert: duplicate check, add at end;   linear cost   $O(n)$
- delete: find, copy last into gap;   linear cost  $O(n)$
- union: copy s1, insert each item from s2;   quadratic cost   $O(nm)$
- intersect: scan for each item in s1;   quadratic cost   $O(nm)$
[^8]
<br>

Same data structure as for unsorted array.

Differences in:

- membership test ... can use binary search
- insertion ... binary search and then shift up and insert
- deletion ... binary search and then shift down

Costs for set operations on sorted array:

- card: read from struct;   $O(1)$
- member: binary search;   $O(log n)$
- insert: find, shift up, insert;   $O(n)$
- delete: find, shift down;   $O(n)$
- union: merge = scan s1, scan s2;   $O(n)$  (technically $O(n+m)$)
- intersect: merge = scan s1, scan s2;   $O(n)$   (technically $O(n+m)$)

### Sets as Linked Lists 
#
[example in slide 25/30]
<br>

1. Concrete data structure (in C):

```
typedef struct Node {
   int  value;
   struct Node *next;
} Node;

struct SetRep {
   Node *elems;  // pointer to first node
   Node *last;   // pointer to last node
   int nelems;   // number of nodes
};
```

2. Set creation:

```
// create new empty set
Set newSet()
{
   Set s = malloc(sizeof(struct SetRep));
   if (s == NULL) {...}
   s->nelems = 0;
   s->elems = s->last = NULL;
   return s;
}
```

3. Checking membership:

```
// set membership test
int SetMember(Set s, int n)
{
   // assert(isValid(s));
   Node *cur = s->elems;
   while (cur != NULL) {
      if (cur->value == n) return true;
      cur = cur->next;
   }
   return false;
}   
```
<br>

4. Costs for set operations on linked list:

- insert: duplicate check, insert at head;   $O(n)$
- delete: find, unlink;   $O(n)$
- member: linear search; $O(n)$
- card: lookup; $O(1)$
- union: copy s1, insert each item from s2; $O(nm)$
- intersect: scan for each item in s1;   $O(nm)$
[^9]

> If we don't have nelems, card becomes O(n)


[table of set implementations in slide 30].

## Trees and Binary search trees
#
### Searching
#
Search is an extremely common application in computing

- given a (large) collection of items and a key value
- find the item(s) in the collection containing that key
  - item = (key, val1, val2, …)  (i.e. a structured data type)
  - key = value used to distinguish items  (e.g. student ID)

>Applications:  Google,  databases, .....

- Many approaches have been developed for the "search" problem

- Different approaches determined by properties of data structures:
  - arrays: linear, random-access, in-memory
  - linked-lists: linear, sequential access, in-memory
  - files: linear, sequential access, external

> Search costs:
[table in slide 2/45]

Maintaining arrays and files in sorted order is costly.

Search trees are efficient to search but also efficient to maintain.

>Example: the following tree corresponds to the sorted array [2,5,10,12,14,17,20,24,29,30,31,32]:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/bigtree.png)

### Tree Data Structures
#
Trees are connected graphs

- with nodes and edges (called links), but no cycles  (no "up-links")
- each node contains a data value   (or key+data)
- each node has links to ≤ k other child nodes   (k=2 below)
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree.png)

Trees are used in many contexts, e.g.

- representing hierarchical data structures (e.g. expressions)
- efficient searching (e.g. sets, symbol tables, …)
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees.png)

> Real-world example: organisational structure
 ![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example1.png)
> Real-world example: hierarchical file system  (e.g. Linux) 
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example2.png)
> Real-world example: structure of a typical book
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example3.png)
> Real-world example: a decision tree  
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example4.png)

A binary tree is either

- empty   (contains no nodes)
- consists of a node, with two subtrees
  - node contains a value  (typically key+data)
  - left and right subtrees are binary trees  (recursive)
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/subtrees.png)

Other special kinds of tree

- m-ary tree: each internal node has exactly m children
- B-tree: each internal node has n/2 ≤ #children ≤ n
- Ordered tree: all left values < root, all right values > root
- Balanced tree: has ≅ minimal height for a given number of nodes
- Degenerate tree: has ≅maximal height for a given number of nodes

### Binary Search Trees
#
Binary search trees (or BSTs) are ordered trees

- each node is the root of 0, 1 or 2 subtrees
- all values in any left subtree are less than root
- all values in any right subtree are greater than root
- these properties applies over all nodes in the tree

Level of node = path length from root to node

Height (or depth) of tree = max path length from root to leaf 
(root is the top of the tree (first circle) and leaf is the bottom most values).

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree-depth.png)

Some properties of trees ...

- Ordered
  - ∀ nodes: max(left subtree) < root < min(right subtree)
- Perfectly-balanced tree
  - ∀ nodes: abs(number_of_nodes(left subtree) - number_of_nodes(right subtree)) <= 1
- Height-balanced tree
  - ∀ nodes: abs(height(left subtree) - height(right subtree)) <= 1

> Note:  time complexity of a balanced tree algorithm is typically O(height)

Operations on BSTs:

- ```insert(Tree,Item)``` … add new item to tree via key
- ```delete(Tree,Key)``` … remove item with specified key from tree
- `search(Tree,Key)` … find item containing key in tree
- plus, "bookkeeping" … new(), free(), show(), …

> Notes:
<br>
> - nodes contain Items; we generally show just Item.key
<br>
> - keys are unique   (not technically necessary)

Examples of binary search trees: 
- balanced trees
- non-balanced trees

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/binary-search-trees.png)

Shape of tree is determined by order of insertion.

### Insertion into BSTs
#

Steps in inserting values into an initially empty BST 

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert0.png)

Example:

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert1.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert2.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert3.png)

### Representing BSTs
#
Binary trees are typically represented by node structures

- where each node contains a value, and pointers to child nodes
- Most tree algorithms move down the tree.
- If upward movement needed, add a pointer to parent.
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree-rep.png)

Typical data structures for trees …

```
// a Tree is represented by a pointer to its root node
typedef struct Node *Tree;

// a Node contains its data, plus left and right subtrees
typedef struct Node {
   int  data;
   Tree left, right;
} Node;

// some macros that we will use frequently
#define data(node)  ((node)->data)
#define left(node)  ((node)->left)
#define right(node) ((node)->right)
```

Here we use a simple definition for `data` ... just a key

Abstract data vs concrete data …

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/concrete.png)

### Searching in BSTs
#

1. Most tree algorithms are best described recursively:

```
TreeContains(tree,key):
|  Input  tree, key
|  Output true if key found in tree, false otherwise
|
|  if tree is empty then
|     return false
|  else if key < data(tree) then
|     return TreeContains(left(tree),key)
|  else if key > data(tree) then
|     return TreeContains(right(tree),key)
|  else         // found
|    return true
|  end if
```

2. Insert an item into a tree;  item becomes new leaf node

```
TreeInsert(tree,item):
|  Input  tree, item
|  Output tree with item inserted
|
|  if tree is empty then
|     return new node containing item
|  else if item < tree->data then
|     tree->left = TreeInsert(tree->left,item)     
|     return tree
|  else if item > tree->data then
|     tree->right = TreeInsert(tree->right,item)     
|     return tree
|  else
|     return tree    // avoid duplicates
|  end if
```

#
[^1]: the general pattern depends on k, number of steps before the seach stops.
  $log{_2}{N}$ = k

[^2]: use Arithmetic Progression Sum to find the estimated running times; (like 1 + 2 + ... + n = n/2 (1 + n) !!!)

[^3]: Beware: NP stands for "nondeterministic, polynomial time (on a theoretical Turing Machine)"

[^4]: Computational complexity theory deals with different degrees of intractability

[^5]: provide operations on new data types essentially

  you create it essentially (to fit your own needs)

  make sure the user does not need to look at the implementation; as long as it can be flexible and can be used

  ie behaviour of the function does not change

  also need to design interface

[^6]: usually header files

[^7]: $ptr(x') == ptr(x)$

[^8]: Assuming: s1 has n items, s2 has m items

[^9]: Assume n = size of s1, m = size of s2