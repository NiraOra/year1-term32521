
#include "list.h"

static bool returnListOrdered(Node n);

bool listIsOrdered(List l) {
	// return if list is ordered
	return returnListOrdered(l->head);
}

static bool returnListOrdered(Node n) {
	// if there is nothing in the list or end of list reached, 
	// return true
	if ((n == NULL) || (n->next == NULL)) {
		return true;
	} else if (n->next->value >= n->value) {
		// if it satisfies the condition that the next val is 
		// greater than one before, return true
		return returnListOrdered(n->next);
	} else {
		// else return false
		return false;
	}
}
