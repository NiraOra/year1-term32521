## First Lesson
<p>
- Each README.md is a lecture for the <b>WEEK</b> 
</p>

### General stuff
#

- warm welcome ? I suppose
- Core of code is algorithms
- course email: cs2521@cse.unsw.edu.au
- ed forum is preferred for questions

### 1511 vs 2521
#
- you start thinking like a computer scientist (look at problem, data needed, how to store it)
- what combination
- analyse behaviour/correctness

### Pre conditions (pre-requisite knowledge)
#
- produce a correct C program
- understand state-based model of computation
- use fundamental C data structures (char, int, float, etc)
- use fundamental control structures (if, while)
- implement abstraction via function declarations, ADTs
- fix simple bugs in incorrect programs
- structs, pointers, malloc, linked lists

### Post conditions
#
- analyse performance characteristics
- measure performance behaviour
- choose/develop effective data structures
- package a set of DS+A as an abstract
- etc.

### Major themes
#
- analyse correctness !!!!

### Schedule per week
#
- 4 hours per week
- lectures contain
  - summary of content
  - problem solving exercises
 ```
example code 
 ``` 

### Tutes and labs
#
- run from week 1 to 10
- exercises for week x available in week x - 1
- similar to comp1511
- 8 labs; take best 7 of 8
- quiz: 8 quizes, take best 7 of 8

### Assignments
#
- first 15%, second is 20%
- generally on binary search tree and graph data structure
- late penalties apply if you miss deadline

### Exam
#
- final exam: <b>in lab, supervised </b>
- 3 hours

### COMP2521 style
#
- can use for loops
- use indentation
- use break
- can use if, switch, while, for, break, continue
- put function start bracket

more stuff
  - can assign statements in expressions (shoudl continue to avoid other kinds of side effects)
  - can use conditional expressions

  Example (boolean): 
```
x = c ? e1 : e2
```
Logic: if c is true, x = e1.
```
if (c) {
  return x = e1;
} else {
  return x = e2;
}
```

- functions may have multiple return statements
  - use very sparingly, primarily for error handling
- gives freedom and power
- more choice in how to express
- can write code which is more concise 
- however, it can be incomprehensible (so, must still use some discipline)

### Switch Statements
#
- The default
```
  switch (v) {
    case C1: 
      S1; break;
    case C2: 
      S2; break;
      ...
    case Cn: 
      Sn; break;
    default:
      Sn+1;
  }
```

Example:
- Given an integer, give month between 1 - 12.
```
int main (int argc, char *argv[]) {
  if (argc > 2) giveUp(argc);
  if (argv[0] > 12 || argv[0] < 1) giveUp(argv[0]);
  
  char *monthName;

  switch (argc) {
    case 1: 
      monthName = "January";
      break;
    case 2: 
      monthName = "February";
    ....
  }
}
```

Example 2:
```
sum = 0;
for (i = 0; i < 10; i++) {
  sum += i;
} [instead of while loops]
```

### Printing sequence
#
```
seqq 10 
```
This prints "1 2 3 4 5 6 ... 10"

```
seq 5 10
```
Prints "5 6 7 8 9 10"

``` 
seq 1 3 10
```
Prints "1 4 7 10"

- other exercises in the files

## Second Lesson
#
<i> code (under lectureCode(2)) </i>
1. Compilation & Makefile
2. Recursion

### Compilation and Makefiles
#
<p>Compilers are programs that convert program source code to executable form; (executable: machine code or bytecode) </p>

1. GCC (gnu C compiler)
  - applied source to source transformation (pre-processor)
  - compiles source code to produce object files (ending with .o)
  ```
  example.o
  ````
  - links object files and libraries to produce executables

2. clang (c lang)
  - available in cse
- dcc and 3c are wrapped around gcc/clang
  

> The compilers use something known as 'sanitizers'

### Processes in Compilers
#
1. Pre Processing
2. Compilation
3. Linking

example:

> prog.c [source] (3 ways in compilation)
> 1. gcc -E -> prog.c' -> step 2
> 2. gcc -c -> prog.o (relocatable binary) -> step 3
> 3. gcc -o -> prog (executable)

Key:
```
-o: output
.o: binary file
-c: object file 
-E: pre -processing
c': pre-processed version
```

<u>Multiple C Files: </u>


> 1. all .h and .c files -> gcc -c (compile)
> 2. gcc -c -> .o files (relocatable binaries)
> 3. .o files + .a files (system libraries) -> gcc -o
> 4. gcc -o (link) -> a.out

### Makefiles
#
make command assists compilation by allowing:
- programmers to document dependencies in code
- minimal re-compilation, based on dependencies

(header files have function definitions)

- header files included in the "main" file so that the main.c won't complain (header files will make sure that the implementation is smoother)


Here:
> 1. gcc -c makes an executable file (Stack.o)
> 2. gcc -c .o files makes a.out
> 3. gcc -o ____ (output file name) .o files makes a file named _____

These three steps can be condensed using Makefile.

(makefile maintains timestamps, everything else)

```
rbt : brackets.o Stack.o
	gcc -o rbt brackets.o Stack.o

brackets.o : brackets.c Stack.h
	gcc -Wall -Werror -c brackets.c

Stack.o : Stack.c Stack.h
	gcc -Wall -Werror -c Stack.c

clean : 
	rm -f *.o rbt 
```
(the exact descriptions are given in the makefile itself)

(if you want to start from scratch, use the following code in the terminal:)
```
$ make clean
```
- whenever you write makefile code, always put tab character instead of spaces (as spaces give compilation error)

### Makefiles and consistencies
#
<p>Makefiles can contain variables.</p>

### Recursion
#
- Recursion is a pattern that calls itself
- for example, n!
- We can recursively define factorial function as f(n) = 1 [if n = 0]; f(n) = n * f(n - 1) [for others]

### Recursive casse
#
- we call the same function for the problem with smaller size
- decrease in a problem size will eventually lead to a "base case"

```
// return sum of list data fields using recursive call
// linked list recursion

int sum (struct node *head) {
  if (head == NULL) {
    return 0;
  } 
  return head->data + sum(head->next);

  // sum(head->next): sum of rest of the list; calling the same function inside the function
} 
```

Another example: last node

```
struct node *last (struct node *head) {
  // list is empty
  if (head == NULL) {
    return NULL;
  }

  // found last node! return it
  else if (head->next == NULL) {
    return head;
  }

  // return last node from the rest of the list using recursion
  else {
    return last(head->next);
  }
}
```