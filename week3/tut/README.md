## Tute (week 3)
#
Time Complexity: worst case

Types:
- ```O(1)```: constant complexity
Example:
```
void print() {
  printf
  printf
}

// this is also O(1): runs 10 times 
int i = 0;
while (i < 10) {
  printf("Hello\n");
  i++;
}
```
- ```O(n)```
```
int i = 0;
while (i < n) {
  printf("Hello\n");
  i++;
}
```

- ```O(n^2)```
```
// could be O(m*n) (as x != y) or O(n^2) worst case
scanf("%d", &x);
scanf("%d", &y);
scand
int i = 0;
while (i < x) {
  int j = 0;
  while (j < y) {
    printf("Hello\n");
  }
  i++;
}
```

- ```O(log(n))``` : cutting down arrays in halves

> logarithms: since c uses binary; log has a base of 2
<br>
  
  - example: binary search

<u> Tute questions </u>

1. (in code file)
3. For two while loops; get the sum of the complexities using the triangle inequality (to get 1/2 n (n - 1); then you get $O(n^2)$).
