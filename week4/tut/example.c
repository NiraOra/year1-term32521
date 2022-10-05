#include <stdio.h>

typedef struct BSTNode *BSTree;
typedef struct BSTNode {
	int value;
	BSTree left;
	BSTree right;
} BSTNode;

int BSTreeeNumNodes(BSTree t) {
  // count nodes in the tree
  if (t == NULL) {
    return 0;
  } 
  // count left path + count right path
  // return result 
  // 1 + the sub tree (keeps adding 1)
  return 1 + BSTreeeNumNodes(t->left) + BSTreeeNumNodes(t->right);
}

int BSTreeCountOdds(BSTree t) {
  // go through every node
  if (t == NULL) {
    return 0;
  }
  // check if it is odd; 
  // add to count if true
  int count = 0;
  if (t->value % 2 == 1) {
    count = 1;
  }

  return count + BSTreeCountOdds(t->left) + BSTreeCountOdds(t->right);

}

int BSTreeHeight(BSTree t) {
  // check the height of the tree
  // check the left and right subtrees

  // need to take the maximum ; longest path
  if (t == NULL) {
    return -1;
  }

  int l = BSTreeHeight(t->left);
  int r = BSTreeHeight(t->right);
  return 1 + ((l > r) ? l : r);
  // 1 + ((l > r) ? l : r) does not work if u return 0; therefore
  // return -1 when t == NULL so it can parse through the condition
  // where t == NULL
}

int BSTreeCountInternal(BSTree t) { 
  // count internal nodes 
  // nodes in total
  // internal: at least one non-empty subtree
  // ie if (t->left == NULL && t->right == NULL), it is not an internal node
  if ((t->left == NULL && t->right == NULL) || (t == NULL)) {
    return 0;
  }

  return 1 + BSTreeCountInternal(t->left) + BSTreeCountInternal(t->right);
}

int BSTreeNodeLevel(BSTree t, int key) { 
  // level of root node == 0
  // need to check through the tree
  // anytime you go by left/right; level increases; even if it points to NULL
  // return: level of node if node exists; otherwise -1
  if (t == NULL) {
    // otherwise case
    return -1;
  }

  if (t->value == key) {
    // found
    // return our level
    return 0;
  }

  // Binary Search
  if (key < t->value) {
    // search left
    int l = BSTreeNodeLevel(t->left, key);
    return (l == -1) ? -1 : l + 1;
  } else {
    // search right
    int r = BSTreeNodeLevel(t->right, key);
    return (r == -1) ? -1 : r + 1;
  }

}