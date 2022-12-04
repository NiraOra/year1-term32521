
#include "list.h"

static void deleteFromList(List l, int val);

int listDeleteLargest(List l) {
	int bigNum = 0;
	for (Node begin = l->head; begin != NULL; begin = begin->next) {
		if (begin->value > bigNum) {
			bigNum = begin->value;
		}
	}
	deleteFromList(l, bigNum);
	return bigNum;
}

static void deleteFromList(List l, int val) {
	Node prev = NULL;
	Node curr = l->head;
	while (curr->value != val) {
		prev = curr;
		curr = curr->next;
	}
	
	if (curr == l->head) {
		l->head = curr->next;
	} else {
		prev->next = curr->next;
	}
	free(curr);
}
