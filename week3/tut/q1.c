#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPalindrome(char *s);

int main(int argc, char *argv[]) {
  if(argc == 2) {
    if (isPalindrome(argv[1])) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }
}

bool isPalindrome(char *s) {
  int frontIndex = 0;
  int backIndex = strlen(s) - frontIndex;
  while (frontIndex < backIndex){
      if (s[frontIndex] != s[backIndex]) {
          return false;
      }
      frontIndex++;
      backIndex--;    
  }
  return true;
}

// check ith letter and n - ith letter

// pseudocode
/*
isPalindrome(A[n]) {
  frontIndex = 0;
  backIndex = n - i;
  while (frontIndex < backIndex):
      if A[frontIndex] != A[backIndex]:
          return false
      frontIndex++;
      backIndex--;    
  
  return true;
}
*/

// Time complexity: 
// `  O(n): worst case wrong letters are in tje middle; check half of the letters
//    actual run time: n/2

