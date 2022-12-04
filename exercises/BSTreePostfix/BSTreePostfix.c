
#include <stdio.h>

#include "BSTree.h"

void BSTreePostfix(BSTree t) {
	// TODO
	// if tree is NULL, return
	if (t == NULL) {
		return;
	} else if (t->left == NULL && t->right == NULL) {
		// print value first if a leaf node
		printf("%d ", t->value);
	} else {
		// do the same for left right subtrees, then print
		// value and return
		BSTreePostfix(t->left);
		BSTreePostfix(t->right);
		printf("%d ", t->value);
		return;
	}

	// or
	/*
	if (t != NULL) {
		BSTreePostfix(t->left);
		BSTreePostfix(t->right);
		printf("%d ", t->value);
	}
	*/
}

