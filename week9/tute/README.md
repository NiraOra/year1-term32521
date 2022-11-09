## Tute

Sorting Algorithms

- Stability: sorting algo is stable 
- Adaptability: time complexity changes based on how sorted the input is
- Comparison: <, >, = operators
- non-comp based = modulo sort, index sort

Sorts
1. Selection sort
```
int a[] = {4, 3, 6, 8, 2};

1. first take 2 (starting from 4 find the smallest value), then swap order to get:
int a[] = {2, 3, 6, 8, 4};

2. go to end from 3, everything is bigger than 3
int a[] = {2, 3, 6, 8, 4};

3. go from 6, we see 4 is smallest, swap
int a[] = {2, 3, 4, 8, 6};

4. one other element, swap 
int a[] = {2, 3, 4, 6, 8};


```

2. Bubble sort
```
int a[] = {4, 3, 6, 8, 2};

1. start from 4, check 3; 4 > 3, swap 3, 4
int a[] = {3, 4, 6, 8, 2};

2. for 4, 6, 8 doesn't hold.

3. 8 > 2;
int a[] = {3, 4, 6, 2, 8};

4. from start, 6 > 2
int a[] = {3, 4, 2, 6, 8};

5. start from 3, 4 > 2;
int a[] = {3, 2, 4, 6, 8};

6. start from 3, 3 > 2
int a[] = {2, 3, 4, 6, 8};

```

3. Insertion sort

```
int a[] = {4, 3, 6, 8, 2};

1. check 3, moves left
int a[] = {3, 4, 6, 8, 2};

2. check 6, is ok
3. check 8, is ok

4. check 2, check to the left till you reach the element less than 2; doesn't hold true, so insert at the leftmost

int a[] = {2, 3, 4, 6, 8};

// don't check leftmost side because we believe it is already sorted (going from left to rights)


```

- i++: post incrementation
```
A[i++] = A[i] then i++

```
- ++i: pre incrementation
```
A[++i] = A[i + 1] (i + 1 = i [sort of])

```