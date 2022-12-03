
#include "list.h"

bool listIsPalindromic(List l) {
	// node first: first node in list
	// node last: last node in list
	Node begin = l->first; 
	Node end = l->last;
	// for half of the list size: don't need to access more than 
	// half cuz iterating unnecessary places otherwise (made an integer division on purpose)
	for (int i = 0; i < (l->size)/2; i++) {
		// if the values from front and back don't compare,
		// not a palindrome: return false
		if (begin->value != end->value) {
			return false;
		}
		// iterate accordingly
		begin = begin->next;
		end = end->prev;
	}
	// return true otherwise
	return true;
}

