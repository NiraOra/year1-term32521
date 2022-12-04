
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	if (t == NULL) {
		// return -1 if:
		// 1. there is no tree
		// 2. not in tree
		return -1;
	} else if (key == t->value) {
		// return 0 if the key is the root
		return 0;
	} else if (key < t->value) {
		// if depth is -1, return -1 or return depth + 1
		int depth = BSTreeNodeDepth(t->left, key);
		return (depth == -1 ? -1 : depth + 1);
	} else {
		// if depth is -1, return -1 or return depth + 1
		int depth = BSTreeNodeDepth(t->right, key);
		return (depth == -1 ? -1 : depth + 1);
	}
}

