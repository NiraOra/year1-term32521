#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void) {
  char *cute = "hello";
  char *file = ".txt";
  strcat(cute, file);
  printf("%s\n", cute);
  
  /*FILE *world = fopen("hello.txt", "rb");
  char *name = malloc(sizeof(char *));
  int size = 0;
  while (fscanf(world, " %s", name) != EOF) {
    size++;
  }
  
  char space[size][10];
  // int number = 0;
  fseek(world, 0, SEEK_SET);
  size = 0;
  while (fscanf(world, " %s", name) != EOF) {
    printf("%s\n", name);
    strcpy(space[size], name);
    size++;
  }*/


  /*
  while (1) {
    char r = (char)fgetc(world); 
    int k = 0; 
    while(r != ' ' && !feof(world)){ //read till , or EOF 
        name[size][k++] = r;         //store in array , 2 character in this example and k+1 (go to next column)
        r = (char)fgetc(world); 
    } 
    name[size][k]=0;     //make last character of string null  
    if(feof(world)){     //check again for EOF 
        break; 
    } 
    
    size++;
  }
  */
  // name[0] = "hello";
  // name[1] = "world";
  /*
  for (int i = 0; i < 2; i++) {
    printf("%s\n", space[i]);
  }
  
  while (fgetc(world) != '\0') {
    fgets(name, 81, world);
  }
  */
  // free(space);
  // free(result);
  // free(name);
  // printf("%d\n", size);
  // fclose(world);
  return 0;
}