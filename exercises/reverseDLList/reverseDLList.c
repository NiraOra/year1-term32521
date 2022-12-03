
#include "list.h"

static void swap(Node *ptr1, Node *ptr2);

void reverseDLList(List l) {
	Node curr = l->first;
	while (curr != NULL) {
		swap(&(curr->prev), &(curr->next));
		curr = curr->prev;
	}

	swap(&(l->first), &(l->last));
}

static void swap(Node *ptr1, Node *ptr2) {
	Node temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}