// COMP 2521 beginning
//
// Pride on hold
// Niranjana (z5417727@unsw.edu.au)
//
// Written: 6/09/22

#include <stdio.h>

struct smth {
  int word;
  struct next *smth;
};

int main(void) {
  printf("This is . going to be bad. this is how the style guide is meant to be.\n");
  struct smth hero;
  hero.word = 9;
  printf("%d\n", hero.word);
  return 0;
}