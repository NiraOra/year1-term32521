#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 7

int main(void) {
  int array[2] = { 1, 2 };
  int arraySize = sizeof (array) / sizeof (array[0]);
  int *ar = malloc(sizeof (int *) * MAX_SIZE);
  ar[0] = 1;
  ar[1] = 2;
  ar[2] = 3;
  ar[3] = 4;
  int size = sizeof(ar);
  int sizeTwo = sizeof(ar[0]);
  int arrayTwoSize = sizeof (ar) / sizeof (ar[0]);
  int arrayThree = *(&ar + 1) - ar;
  printf
    ("Array 1 size (with no malloc) : %d, Array two size (with malloc) [%d]/[%d]: %d, Malloced Array with pointer arithmetic: %d\n",
     arraySize, size, sizeTwo, arrayTwoSize, arrayThree);
  free(ar);
  return 0;
}



