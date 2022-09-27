## Week 3
#
## First Lecture
#
> For binary trees, it is always good to seperate into two different trees (left tree vs right tree) based on logic
[check lecture code wooooooo]
## Second Lecture
#
> Binary Tree: Still in lecture Code
> checking height of the tree

### Tree Data Structures
#
Trees are connected graphs

- with nodes and edges (called links), but no cycles  (no "up-links")
- each node contains a data value   (or key+data)
- each node has links to ≤ k other child nodes   (k=2 below)
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree.png)

Trees are used in many contexts, e.g.

- representing hierarchical data structures (e.g. expressions)
- efficient searching (e.g. sets, symbol tables, …)
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees.png)

> Real-world example: organisational structure
 ![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example1.png)
> Real-world example: hierarchical file system  (e.g. Linux) 
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example2.png)
> Real-world example: structure of a typical book
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example3.png)
> Real-world example: a decision tree  
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/trees_example4.png)

A binary tree is either

- empty   (contains no nodes)
- consists of a node, with two subtrees
  - node contains a value  (typically key+data)
  - left and right subtrees are binary trees  (recursive)
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/subtrees.png)

Other special kinds of tree

- m-ary tree: each internal node has exactly m children
- B-tree: each internal node has n/2 ≤ #children ≤ n
- Ordered tree: all left values < root, all right values > root
- Balanced tree: has ≅ minimal height for a given number of nodes
- Degenerate tree: has ≅maximal height for a given number of nodes

### Binary Search Trees
#
Binary search trees (or BSTs) are ordered trees

- each node is the root of 0, 1 or 2 subtrees
- all values in any left subtree are less than root
- all values in any right subtree are greater than root
- these properties applies over all nodes in the tree

Level of node = path length from root to node

Height (or depth) of tree = max path length from root to leaf 
(root is the top of the tree (first circle) and leaf is the bottom most values).

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree-depth.png)

Some properties of trees ...

- Ordered
  - ∀ nodes: max(left subtree) < root < min(right subtree)
- Perfectly-balanced tree
  - ∀ nodes: abs(number_of_nodes(left subtree) - number_of_nodes(right subtree)) <= 1
- Height-balanced tree
  - ∀ nodes: abs(height(left subtree) - height(right subtree)) <= 1

> Note:  time complexity of a balanced tree algorithm is typically O(height)

Operations on BSTs:

- ```insert(Tree,Item)``` … add new item to tree via key
- ```delete(Tree,Key)``` … remove item with specified key from tree
- `search(Tree,Key)` … find item containing key in tree
- plus, "bookkeeping" … new(), free(), show(), …

> Notes:
<br>
> - nodes contain Items; we generally show just Item.key
<br>
> - keys are unique   (not technically necessary)

Examples of binary search trees: 
- balanced trees
- non-balanced trees

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/binary-search-trees.png)

Shape of tree is determined by order of insertion.

### Insertion into BSTs
#

Steps in inserting values into an initially empty BST 

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert0.png)

Example:

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert1.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert2.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/insert3.png)

### Representing BSTs
#
Binary trees are typically represented by node structures

- where each node contains a value, and pointers to child nodes
- Most tree algorithms move down the tree.
- If upward movement needed, add a pointer to parent.
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree-rep.png)

Typical data structures for trees …

```
// a Tree is represented by a pointer to its root node
typedef struct Node *Tree;

// a Node contains its data, plus left and right subtrees
typedef struct Node {
   int  data;
   Tree left, right;
} Node;

// some macros that we will use frequently
#define data(node)  ((node)->data)
#define left(node)  ((node)->left)
#define right(node) ((node)->right)
```

Here we use a simple definition for `data` ... just a key

Abstract data vs concrete data …

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/concrete.png)

### Searching in BSTs
#

1. Most tree algorithms are best described recursively:

```
TreeContains(tree,key):
|  Input  tree, key
|  Output true if key found in tree, false otherwise
|
|  if tree is empty then
|     return false
|  else if key < data(tree) then
|     return TreeContains(left(tree),key)
|  else if key > data(tree) then
|     return TreeContains(right(tree),key)
|  else         // found
|    return true
|  end if
```

2. Insert an item into a tree;  item becomes new leaf node

```
TreeInsert(tree,item):
|  Input  tree, item
|  Output tree with item inserted
|
|  if tree is empty then
|     return new node containing item
|  else if item < tree->data then
|     tree->left = TreeInsert(tree->left,item)     
|     return tree
|  else if item > tree->data then
|     tree->right = TreeInsert(tree->right,item)     
|     return tree
|  else
|     return tree    // avoid duplicates
|  end if
```