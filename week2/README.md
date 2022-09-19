## Second Week
#
### First lecture
#
### Continuing from Recursion
#

Deleting from list using Recursion:
```
struct node *deleteR (struct node *list, int value) {
  if (list == NULL) {
    fprintf(stderr, "warning: value %d is not in list\n");
  } else if (list->data == value) {
    struct node *tmp = list;
    list = list->next; // remove first item
    free(tmp);         // free the value
  } else {
    list->next = deleteR(list->next, value);  // recursive call to deleteR function with the next address of the list
  }
  return list;
}
```

Print Python List using Recursion:
```
// print contents of list in Python Syntax

void print_list(struct node *head) {
  printf("[");
  if (head != NULL) {
    print_list_items(head); 
  }
  printf("]");
}

// recursive function
void print_list_items(struct node *head) {
  printf("%d", head->data);
  if (head->next != NULL) {
    printf(", ");
    // recursive call
    print_list_items(head->next);
  }
}
```