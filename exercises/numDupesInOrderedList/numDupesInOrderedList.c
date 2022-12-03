
#include "list.h"

int numDupesInOrderedList(List l) {
	int count = 0;
	Node curr = l->head;
	while (curr != NULL && curr->next != NULL) {
		if (curr->value == curr->next->value) {
			count++;
		}
		curr = curr->next;
	}
	return count;
}


