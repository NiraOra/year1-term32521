#include <stdio.h>
#include <stdlib.h>
#include "CodeRun.h"
#include <string.h>
#include <assert.h>

#define QUIT 'q'
#define QUIZ_QUESTION 'Q'

int main(int argc, char *argv[]) {
  //Testing quiz 2 question 6
  // assert(argc > 1);
  showCommand();
  printf("Makefile works!! my god\n");
  char quit;
  printf("> ");
  while (scanf(" %c", &quit) != -1) {
    if (quit == QUIT) {
      exit(1);
    }
    if (quit == QUIZ_QUESTION) {
      chooseFromWeek();
    }
  }
  
  struct node *new = malloc(sizeof(*new));
  struct node *newTwo = malloc(sizeof(*newTwo));
  struct node *newThree = malloc(sizeof(*newThree));
  //struct node *newFour = malloc(sizeof(*newFour));
  //struct node *newFive = malloc(sizeof(*newFive));
  new->data = 8;
  newTwo->data = 2;
  newThree->data = 6;
  //newFour->data = 4;
  //newFive->data = 2;
  new->next = newTwo;
  newTwo->next = newThree;
  newThree->next = NULL;
  //newFour->next = NULL;
  //newFive->next = NULL;
  
  // struct node *head = fn(new);
  
  //struct node *new = NULL;
  //struct node *newTwo = create_node(3);
  //new->next = newTwo;
  new = append(new, 7);
  print(new);
  

}

void showCommand() {
  printf("Choose From the following:\n");
  printf("1. Quit: q\n");
  printf("2. Quiz Question: q_q\n");
  printf("3. Print: p\n");
}

void chooseFromWeek() {
  printf("Choose From the following:\n");
  printf("1. Week 2\n");
  printf("2. Week 3\n");
  printf("3. Week 4\n");
  printf("4. Week 5\n");
  printf("5. Week 7\n");
  printf("6. Week 8\n");
  printf("7. Week 9\n");
}

// reveres list; list2 is like a new head (2-> last node of the first), and the list2 is updated accordingly
// quiz2 q6
struct node *fn(struct node *head) {
  if (head == NULL) {
    return NULL;
  }
  if (head->next == NULL) {
    return head;
  }
  struct node *list2 = fn(head->next);
  head->next->next = head;
  head->next = NULL;
  return list2;

}

// quiz 2 question 4
struct node *append(struct node *list, int value) {
  if (list->next == NULL) {
    // in the quiz
    //return create_node(value);
    
    //ideal solution:
    struct node *temp = create_node(value);
    return list->next = temp;
    
  } else {
    append(list->next, value);
    return list;
  }
}

struct node *create_node(int value) {
  struct node *new = malloc(sizeof(*new));
  new->data = value;
  new->next = NULL;
  return new;
}

// print the values of the linked list
void print(struct node *head) {
  for (struct node *current = head; current != NULL; current = current->next) {
    printf("%d ", current->data);
  }
  printf("\n");
}


