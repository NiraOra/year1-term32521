
#include "tree.h"

static Tree newNode(int value);

Tree TreeCopy(Tree t, int depth) {
	// TODO
	if (t == NULL || depth < 0) {
		return NULL;
	}
	// malloc new node with same value
	Tree new = newNode(t->value);
	// add the subtrees accordingly
	new->left = TreeCopy(t->left, depth - 1);
	new->right = TreeCopy(t->right, depth - 1);
	// return the new Tree
	return new;
}

static Tree newNode(int value) {
	// malloc new node; error if no space
	Tree temp = malloc(sizeof(*temp));
	if (temp == NULL) {
		printf("can't make a new tree node, no space!\n");
		return NULL;
	}
	// assign values and subtrees, then return node
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}


