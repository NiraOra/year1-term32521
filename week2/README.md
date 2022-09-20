## <b> Second Week </b>
#
## <b> First lecture </b>
#
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

## Second Lecture
#


#
[^1]: the general pattern depends on k, number of steps before the seach stops.
  $log{_2}{N}$ = k

[^2]: use Arithmetic Progression Sum to find the estimated running times; (like 1 + 2 + ... + n = n/2 (1 + n) !!!)

[^3]: Beware: NP stands for "nondeterministic, polynomial time (on a theoretical Turing Machine)"

[^4]: Computational complexity theory deals with different degrees of intractability