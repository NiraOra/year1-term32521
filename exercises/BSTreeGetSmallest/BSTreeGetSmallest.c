
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO
	if (t == NULL) {
		return NULL;
	} else if (t->left == NULL) {
		return t;
	} else {
		return BSTreeGetSmallest(t->left);
	}
}

