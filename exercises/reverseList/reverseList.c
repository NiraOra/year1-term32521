
#include "list.h"

void listReverse(List l) {
	// TODO
	if (l == NULL) {
		return;
	} else {
		Node prev = NULL;
		Node curr = l->head;
		while (curr != NULL) {
			Node temp = curr;
			curr = curr->next;
			temp->next = prev;
			prev = temp;
		}
		l->head = prev;
	}
}

