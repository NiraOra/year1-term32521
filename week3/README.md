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

### Tree Traversal
#
Iteration (traversal) on …

- Lists … visit each value, from first to last
- Graphs … visit each vertex, order determined by DFS/BFS/…

For binary Trees, several well-defined visiting orders exist:
- <b>preorder</b> (NLR) … visit root, then left subtree, then right subtree
- <b>inorder</b> (LNR) … visit left subtree, then root, then right subtree
- <b>postorder</b> (LRN) … visit left subtree, then right subtree, then root
- <b>level-order</b> … visit root, then all its children, then all their children

Consider "visiting" an expression tree like:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/tree1.png)

- NLR:  + * 1 3 - * 5 7 9    (prefix-order: useful for building tree) 
- LNR:  1 * 3 + 5 * 7 - 9    (infix-order: "natural" order) 
- LRN:  1 3 * 5 7 * 9 - +    (postfix-order: useful for evaluation) 
- Level:  + * - 1 3 * 9 5 7    (level-order: useful for printing tree)

Traversals for the following tree:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/bigtree.png)

- NLR (preorder):   20   10   5   2   14   12   17   30   24   29   32   31

- LNR (inorder):   2   5   10   12   14   17   20   24   29   30   31   32

- LRN (postorder):   2   5   12   17   14   10   29   24   31   32   30   20

1. Pseudocode for NLR traversal

```
showBSTreePreorder(t):
|  Input tree t
|
|  if t is not empty then
|  |  print data(t)
|  |  showBSTreePreorder(left(t))
|  |  showBSTreePreorder(right(t))
|  end if
```

- Recursive algorithm is very simple.

- Iterative version less obvious ... requires a Stack.

2. Pseudocode for NLR traversal (non-recursive)

```
showBSTreePreorder(t):
|  Input tree t
|
|  push t onto new stack S
|  while stack is not empty do
|  |  t=pop(S)
|  |  print data(t)
|  |  if right(t) is not empty then
|  |     push right(t) onto S
|  |  end if
|  |  if left(t) is not empty then
|  |     push left(t) onto S
|  |  end if
|  end while
```
### Joining Two Trees
#
An auxiliary tree operation …

Tree operations so far have involved just one tree.

An operation on two trees:   ```t = TreeJoin(t1,t2)```

- Pre-conditions:
  - takes two BSTs; returns a single BST
  - max(key(```t1```)) < min(key(```t2```))
- Post-conditions:
  - result is a BST (i.e. fully ordered)
  - containing all items from ```t1``` and ```t2```

Method for performing tree-join:

  - find the min node in the right subtree (t2)
  - replace min node by its right subtree  (possibly empty)
  - elevate min node to be new root of both trees

> Advantage: doesn't increase height of tree significantly

> x ≤ height(```t```) ≤ x+1, where x = max(height(```t1```),height(```t2```))

> Variation: choose deeper subtree; take root from there.  

1. Joining two trees:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/join-op.png) [^1]

<u>Implementation of tree-join:</u>

```
TreeJoin(t1,t2):
|  Input  trees t1,t2
|  Output t1 and t2 joined together
|
|  if t1 is empty then return t2
|  else if t2 is empty then return t1
|  else
|  |  curr=t2, parent=NULL
|  |  while left(curr) is not empty do     // find min element in t2
|  |     parent=curr
|  |     curr=left(curr)
|  |  end while
|  |  if parent≠NULL then
|  |     left(parent)=right(curr)  // unlink min element from parent
|  |     right(curr)=t2
|  |  end if
|  |  left(curr)=t1
|  |  return curr                  // curr is new root
|  end if
```

2. Example tree join:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/treeJoin.png)

### Deletion From BSTs
#
Insertion into a binary search tree is easy.

Deletion from a binary search tree is harder.

Four cases to consider …

- empty tree … new tree is also empty
- zero subtrees … unlink node from parent
- one subtree … replace by child
- two subtrees … replace by successor, join two subtrees

Cases: 

1. item to be deleted is a leaf (zero subtrees)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del-k.png)

> Just delete the items

2. : item to be deleted is a leaf (zero subtrees)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del1-k.png)

3. item to be deleted has one subtree

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del-p.png)

> Replace the item by its only subtree

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del1-p.png)

4. item to be deleted has two subtrees

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del0-m.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del1-m.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del-m.png)

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees/Pics/del2-m.png)


> Version 1: right child becomes new root, attach left subtree to min element of right subtree <br>
> Version 2: join left and right subtree

- Pseudocode (version 2):
```
TreeDelete(t,item):
|  Input  tree t, item
|  Output t with item deleted
|
|  if t is not empty then          // nothing to do if tree is empty
|  |  if item < data(t) then       // delete item in left subtree
|  |     left(t)=TreeDelete(left(t),item)
|  |  else if item > data(t) then  // delete item in left subtree
|  |     right(t)=TreeDelete(right(t),item)
|  |  else                         // node 't' must be deleted
|  |  |  if left(t) and right(t) are empty then 
|  |  |     new=empty tree                   // 0 children
|  |  |  else if left(t) is empty then
|  |  |     new=right(t)                     // 1 child
|  |  |  else if right(t) is empty then
|  |  |     new=left(t)                      // 1 child
|  |  |  else
|  |  |     new=TreeJoin(left(t),right(t))  // 2 children
|  |  |  end if
|  |  |  free memory allocated for t
|  |  |  t=new
|  |  end if
|  end if
|  return t
```
## (new topic)
## Function Pointers in C
#
(Mostly in Slides: giving just small notes)
- memory addresses in the function
- variables/paramanetres declared as:
```typeOfReturnValye (*fp) (typeOfArgument) ```

<u> Function Pointers Example: </u>

- ```int square(int x)``` { return x *x;}
- ```int timesTwo(int x)``` {return x*2;}
- ```int (*fp)(int)```;
- ```fp``` = ```&square```; <br> // fp points to the square function
- ```int n = (*fp)(10)```; //call the square function with input 10
- ```fp = timesTwo```; //works without the & //fp points to the timesTwo function
- ```n = (*fp) (2);```
- ```n = fp(2)``` //can also use normal function call //notation

Higher-order Functions:
- Functions that get other functions as arguments, or return functions as a result

- Example: the function traverse takes a list and a function pointer (fp) as argument and applies the function to all nodes in the list

- Another example: compare functions (here, there can be two compare functions with exactly opposite logics, but function pointers can help parse through the code in an efficient way).

## Balancing Search Trees
#
### Balancing Binary Search Trees
#
Observation: order of insertion into a tree affects its height

- worst case: keys inserted in ascending/descending order (effectively have a linked list, so search cost is O(n) )
- best case (for at-leaf insertion): keys inserted in pre-order (tree height ⇒ search cost is O(log n) ; tree is balanced)
- average case: keys inserted in random order (tree height ⇒ search cost is O(log n ); but cost ≥ best case)

Goal: build binary search trees which have
- minimum height ⇒ minimum worst case search cost

Perfectly-balanced tree with N nodes has

- ∀ nodes,  abs(#nodes(LeftSubtree) - #nodes(RightSubtree)) < 2
- height of log2N ⇒ worst case search O(log N)

Three strategies to improving worst case search in BSTs:
- <b>randomise</b>  —  reduce chance of worst-case scenario occuring
- <b>amortise</b>  —  do more work at insertion to make search faster
- <b>optimise</b>  —  implement all operations with performance bounds

### Operations for Rebalancing
#
To assist with rebalancing, we consider new operations:

1. Left rotation
  - move right child to root; rearrange links to retain order

2. Right rotation
  - move left child to root; rearrange links to retain order
3. Insertion at root
  - each new item is added as the new root node
4. Partition
  - rearrange tree around specified node  (push it to root)

### Tree Rotation
#
Rotation operations:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/left-right-rotation.png)
> Note: tree is ordered,   t1  <  n2  <  t2  <  n1  <  t3

Method for rotating tree T right:

- n1 is current root; n2 is root of n1's left subtree
- n1 gets new left subtree, which is n2's right subtree
- n1 becomes root of n2's new right subtree
- n2 becomes new root
- n2's left subtree is unchanged

> Left rotation: swap left/right in the above. <br>
> Rotation requires simple, localised pointer rearrangemennts <br>
> Cost of tree rotation: O(1)

Example (right rotation):
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/rotr.png)

1. Algorithm for Right Rotation:
```
rotateRight(n1):
|  Input  tree n1
|  Output n1 rotated to the right
|
|  if n1 is empty ∨ left(n1) is empty then
|     return n1
|  end if
|  n2= n1->left
|  n1->left = n2->right 
|  n2->right =n1
|  return n2
```

2. Algorithm for Left Rotation:
```
rotateLeft(n2):
|  Input  tree n2
|  Output n2 rotated to the left
|
|  if n2 is empty ∨ right(n2) is empty then
|     return n2
|  end if
|  n1=n2->right
|  n2->right = n1->left
|  n1->left = n2
|  return n1
```

#
[^1]: Note: ```t2'``` may be less deep than ```t2```