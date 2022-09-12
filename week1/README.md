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