## Tute
#

### For loops
#

```
int i = 10;
while (i >= 0) {
    printf("%d\n", i);
    i--;
}

// for loop
for (int i = 10; i >= 0; i--) {
  printf("%d\n", i);
}
```

### Switch Statements
#

Example:
```
// S1
switch (ch) {
    case 'a': printf("eh? "); break;
    case 'e': printf("eee "); break;
    case 'i': printf("eye "); break;
    case 'o': printf("ohh "); break;
    case 'u': printf("you "); break;
}
printf("\n");
// remember to put break statments
```

Example:
```
char *numToDay(int n) {
	assert(0 <= n && n <= 6);
	char *day;
	if (n == 0) {
		day = "Sun";
	} else if (n == 1) {
		day = "Mon";
	} else if (n == 2) {
		day = "Tue";
	} else if (n == 3) {
		day = "Wed";
	} else if (n == 4) {
		day = "Thu";
	} else if (n == 5) {
		day = "Fri";
	} else if (n == 6) {
		day = "Sat";
	}
	return day;
}
// switch statment

switch(n) {
  case 0: 
    day == "Sun";
    break;
  case 1: 
    day == "Mon";
    break;
  case 2: 
    day == "Tue";
    break;
  case 3: 
    day == "Wed";
    break;
  case 4: 
    day == "Thurs";
    break;
  case 5: 
    day == "Fri";
    break;
  case 6: 
    day == "Sat";
    break;  

}
```

### Ternary Statement
#

```
int ch = getchar();

char *type;
if (isdigit(ch)) {
    type = "digit";
} else {
    type = "non-digit";
}

printf("'%c' is a %s\n", ch, type);

// ternary statement

type = isdigit(ch) ? "digit" : "non digit" ;

```