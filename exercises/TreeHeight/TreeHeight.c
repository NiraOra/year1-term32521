
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    // if no tree, return -1
    if (t == NULL) {
        return -1;
    } else {
        // count node from right
        int rightCount = 1 + TreeHeight(t->right);
        // count node from left
        int leftCount = 1 + TreeHeight(t->left);
        // if left count greater, return left
        // else return rightcount
        return leftCount > rightCount ? leftCount : rightCount;
    }

}

