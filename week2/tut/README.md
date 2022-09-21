## Tut
#
## GCC, makefiles, recursion
#
### GCC
#
1. 
a) gcc -o: object files -> output
b) gcc -c: outputs to standard output (*.o)
c) gcc -E: look into the code
d) gcc -g: debug information (makes a.out)
e) gcc -03: optimise

> manual gcc: gives gcc file options

### Makefile
#

2.

```
tw: tw.o Dict.o stemmer.o         // final "output" -> compilation
tw.o: tw.c Dict.h WFreq.h stemmer.h
Dict.o: Dict.c Dict.h WFreq.h 
stemmer.o: stemmer.c stemmer.h
```
if the *.o files dont exist, it foes to the entries and compiles it to the .o files and then runs the first line. 

3. 
In the beginning of a header file, put this:
(known as a header guard)
```
#ifndef X_H     // if not defined
#define X_H     // define file
// ... rest of X.h file ...
#endif          // end if
```

### Recursion
#
1. Write iterative and recurisve functions to compute length of a linked list

(iterative: how we coded in 1511)
(recursion: call the same function over and over)

1. Iterative
```
typedef struct node {
	int data;
	struct node *next;
} Node;

typedef Node *List;

int listLength(List l) { 
  if (l == NULL) { return 0;
  }

  int size = 0;

  for (List *current = l; current != NULL; current = current->next; ) {
    size++;
  }

  return size;


}
```

2. Recursive
```
typedef struct node {
	int data;
	struct node *next;
} Node;

typedef Node *List;

int listLengthR(List l) { 
  // base case  
  if (l == NULL) { return 0;
  }

  // recursive case (as the listlengthR is technically the size in this case)

  return listLengthR(l->next) + 1;


}
```
<u> Logic </u>

- 1, 2, 3, 4, X
- listlengthR(1)
- return listLengthR(2) + 1

- lisLengthR(2)
- return listLengthR(3) + 1

...

- listLengthR(4)
- return listLengthR(4) + 1 ;
- NULL -> 0
- 0 + 1 + 1 + 1 + 1
- therefore, it returns 4

5. 
(same typedef)
Iterative

```
int listCountOdds(List l) { 
  if (l == NULL) {
    return 0;
  }

  int count = 0;
  for (List current = l; current != NULL; current = current->next) {
    if (c->data % 2 == 1) {
      count++;
    }
  }
  return count;

}

```

Recursive 

```
int listCountOdds(List l) { 
  // base case
  
  if (l == NULL) {
    return 0;
  }

  // recursive odd case

  if (l->data % 2 == 1) {
  return listlengthR(l->next) + 1;
  }
  
  // recursive
  return listLengthR(l->next);
}

```

6. 
(same typedef)
Iterative

// we can look forwards but not backwards


```
bool listIsSorted(List l) { 
  if (l == NULL || l->next == NULL) {
    return true;
  }

  for (List current = l; current != NULL; current = current->next) {
    if (current->data > current->next->data) {
      return false;
    }
  }

  return true;

}

```

Recursive

```
bool listIsSorted(List l) { 
  // base case
  if (l == NULL || l->next == NULL) {
    return true;
  }

  // recursive case - not sorted
  if (l->data > l->next->data) {
    return false;

  }

  // recursive 
  return listSortedR(l->next);
}

```

7. 

Recursive:

```
List listDeleteEvens(List l) { 
  // base case
  if (l == NULL) {
    return NULL;
  }


  // recursive: evens



}

```