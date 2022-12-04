
#include "list.h"

static bool inList(List l, int val);
static void appendToList(List l, int value);

List listSetDifference(List l1, List l2) {
	// TODO
	List diffVal = newList();
	for (Node begin = l1->head; begin != NULL; begin = begin->next) {
		if (inList(l2, begin->value) == false) {
			appendToList(diffVal, begin->value);
		}
	}
	return diffVal;
}

static void appendToList(List l, int value) {
	Node n = newNode(value);
	n->next = l->head;
	l->head = n;
}


static bool inList(List l, int val) {
	for (Node begin = l->head; begin != NULL; begin = begin->next) {
		if (begin->value == val) {
			return true;
		}
	}
	return false;
}

