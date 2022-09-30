#ifndef CODERUN_H
#define CODERUN_H

struct node {
  int data;
  struct node *next;
};

// week 2 quiz question 6: reverses list
struct node *fn(struct node *head);

// week 2 quiz question 4: adds to end of list (doesn't work for values more than NULL)
struct node *append(struct node *head, int value);

// week 2 quiz question 4: creates a new node
struct node *create_node(int value);

// general helper functions
// 1.
void print(struct node *head);
// 2.
void showCommand();
// 3.
void chooseFromWeek();

#endif