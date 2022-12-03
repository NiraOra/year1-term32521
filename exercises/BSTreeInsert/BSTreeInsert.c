
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

static BSTree newBSTNode(int val);

BSTree BSTreeInsert(BSTree t, int val) {
	if (t == NULL) {
		return newBSTNode(val);
	}
	
	if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
	} else if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
	}
	return t;
}

static BSTree newBSTNode(int val) {
	BSTree t = malloc(sizeof(*t));
	if (t == NULL) {
		fprintf(stderr, "couldn't allocate node\n");
		exit(EXIT_FAILURE);
	}
	
	t->value = val;
	t->left = NULL;
	t->right = NULL;
	return t;
}

