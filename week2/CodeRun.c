#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
};

//struct node *fn(struct node *head);
struct node *append(struct node *head, int value);
struct node *create_node(int value);

int main(int argc, char *argv[]) {
  /*
  Testing quiz 2 question 6
  struct node *new = malloc(sizeof(*new));
  struct node *newTwo = malloc(sizeof(*newTwo));
  struct node *newThree = malloc(sizeof(*newThree));
  struct node *newFour = malloc(sizeof(*newFour));
  struct node *newFive = malloc(sizeof(*newFive));
  new->data = 3;
  newTwo->data = 7;
  newThree->data = 5;
  newFour->data = 3;
  newFive->data = 2;
  new->next = newTwo;
  newTwo->next = newThree;
  newThree->next = newFour;
  newFour->next = newFive;
  newFive->next = NULL;
  
   //struct node *head = fn(new);
  */

  struct node *new = create_node(7);
  struct node *newTwo = create_node(3);
  new->next = newTwo;
  new = append(new, 6);
 
  for (struct node *current = new; current != NULL; current = current->next) {
    printf("%d ", current->data);
  }
  printf("\n");

}

// reveres list; list2 is like a new head (2-> last node of the first), and the list2 is updated accordingly
// quiz2 q6
/*struct node *fn(struct node *head) {
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

}*/

// quiz 2 question 4
struct node *append(struct node *list, int value) {
  if (list == NULL) {
    return create_node(value);
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



