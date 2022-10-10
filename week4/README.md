## Week 4
#
## First Lecture
#
## Balancing BSTs
#
### Tree Rotation
#
Rotation operations:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/left-right-rotation.png)
> Note: tree is ordered,   $t_1  <  n_2  <  t_2  <  n_1  <  t_3$

Method:
- n1 is current root; n2 is root of n1's left subtree
- n1 gets new left subtree, which is n2's right subtree
- n1 becomes root of n2's new right subtree
- n2 becomes new root
- n2's left subtree is unchanged
<br>
Left rotation: swap left/right in the above.
Rotation requires simple, localised pointer rearrangemennts

> Cost of tree rotation: O(1)

Example of right rotation:
1. ![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/rotr.png)

2. Algorithm:
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

- Algorithm for Left rotation
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

Cost considerations for tree rotation

- the rotation operation is cheap  O(1)
- if applied appropriately, will tend to improve tree balance

Sometimes rotation is applied from leaf to root, along one branch
- cost of this is O(height)
- payoff is improved balance which reduces height
- reduced height pushes search cost towards O(log n)

### Insertion at root
#
Previous discussion of BSTs did insertion at leaves.

Different approach: insert new item at root.

Potential disadvantages:
- large-scale rearrangement of tree for each insert  (apparently)

Potential advantages:
- recently-inserted items are close to root
- lower cost if recent items more likely to be searched

Method for inserting at root:

1. base case:
- tree is empty; make new node and make it root
2. recursive case:
- insert new node as root of appropriate subtree
- lift new node to root by rotation

Example of inserting at root:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/insert-root.png)

Algorithm for inserting at root:
```
insertAtRoot(t, it):
|  Input tree t, item it to be inserted
|  Output modified tree with item at root
|
|  if t is empty tree then
|     t = new node containing item
|  else if item < t->data then
|     t->left = insertAtRoot( t->left, it)
|     t = rotateRight(t)
|  else if it > root(t) then
|     t->right = insertAtRoot( t->right, it)
|     t = rotateLeft(t)
|  end if
|  return t;
```

Analysis of insertion-at-root:

- same complexity as for insertion-at-leaf:  O(height)
  - but cost is effectively doubled ... traverse down, rotate up
- tendency to be balanced, but no balance guarantee
- benefit comes in searching
  - for some applications, search favours recently-added items
  - insertion-at-root ensures these are close to root
- could even consider "move to root when found"
  - effectively provides "self-tuning" search tree

### Tree Partitioning
#
Tree partition operation partition(tree,i)
- re-arranges tree so that element with index i  becomes root

![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/tindex.png)

> For tree with N nodes, indices are 0 .. N-1, in LNR order

Example of partition:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/partition.png)

Implementation of partition operation:
```
partition(tree,i):
|  Input  tree with n nodes, index i
|  Output tree with ith item moved to the root
|
|  m = number_of_nodes(left(tree))
|  if i < m then
|     tree->left = partition(tree->left, i)
|     tree = rotateRight(tree)
|  else if i > m then
|     tree->right = partition(tree->right , i-m-1)
|     tree = rotateLeft(tree)
|  end if
|  return tree
```

> Note:  size(tree) = n,   size(left(tree)) = m,   size(right(tree)) = n-m-1

Analysis of tree partitioning
- no requirement for search  (using element index instead)
- after each recursive partitioning step, one rotation
- overall cost similar to insert-at-root

Benefits
- tends to improve balance ⇒ improves search cost

### Periodic Rebalancing
#
An approach to maintaining balance:
- insert at leaves as before;   periodically, rebalance the tree
```
|  Input  tree, item
|  Output tree with item randomly inserted
|  // k: number of insertions
|  t=insertAtLeaf(tree,item)
|  if #nodes(t) mod k = 0 then
|     t=rebalance(t)
|  end if
|  return t
```
> When to rebalance?   e.g. after every k insertions

<b>!! A problem with this approach ... </b>

- operation ```#nodes()``` has to traverse whole (sub)tree
- to improve efficiency, change node structure
```
typedef struct Node {
   int  data;
   int  nnodes;      // #nodes in my tree
   Tree left, right; // subtrees
} Node;
```
- But maintaining ```nnodes``` requires extra work in other operations

1. How to rebalance a BST?   Move median item to root.
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/rebalance.png)

2. Implementation:
```
rebalance(t):
|  Input  tree t with n nodes
|  Output t rebalanced
|
|  if n≥3 then
|  |  // put node with median key at root
|  |  t=partition(t,n/2)
|  |  // then rebalance each subtree
|  |  t->left = rebalance(t->left)
|  |  t->right = rebalance(t->right)
|  end if
|  return t
```
Analysis of rebalancing: visits every node ⇒ O(N)

Cost means not feasible to rebalance after each insertion.

When to rebalance? … Some possibilities:
- after every k insertions
- whenever "imbalance" exceeds threshold
E
ither way, we tolerate worse search performance for periods of time.

> Does it solve the problem? … Not completely   ⇒ Solution: real balanced trees  (next week)

### Randomised BST insertion
#
Reminder: order of insertion can dramatically affect shape of tree

Tree ADT has no control over order that keys are supplied.

We know that inserting in random order gives $O(log_{2}{n})$ search

> Can the algorithm itself introduce some randomness?

<u>Approach:</u> normally do leaf insert, randomly do root insert.
```
insertRandom(tree,item)
|  Input  tree, item
|  Output tree with item randomly inserted
|
|  if tree is empty then
|     return new node containing item
|  end if
|  // p/q chance of doing root insert
|  if random() mod q < p then
|     return insertAtRoot(tree,item)
|  else
|     return insertAtLeaf(tree,item)
|  en
```

> E.g. 30% chance ⇒ choose p=3, q=10
Cost analysis:
- similar to cost for inserting keys in random order:  O(log2 n)
- does not rely on keys being supplied in random order

Approach can also be applied to deletion:
- standard method promotes inorder successor to root
- for the randomised method …
  - promote inorder successor from right subtree, OR
  - promote inorder predecessor from left subtree

### Application of BSTs: Sets
#
Trees provide efficient search.

Sets require efficient search
  - to find where to insert/delete
  - to test for set membership

Logical to implement a set ADT via binary search tree.

Assuming we have BST implementation with type ```Tree```
- which precludes duplicate key values
- which implements insertion, search, deletion

then ```Set``` implementation is
- ```SetInsert(Set,Item) ≡ TreeInsert(Tree,Item)```
- ```SetDelete(Set,Item) ≡ TreeDelete(Tree,Item.Key)```
- ```SetMember(Set,Item) ≡ TreeSearch(Tree,Item.Key)```

> What about union? and intersection?
Sets implemented via Trees:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/trees2/Pics/set-tree.png)

Concrete representation:
```
#include <Tree.h>

typedef struct SetRep {
   int   nelems;
   Tree  root;
} SetRep;

Set newSet() {
   Set S = malloc(sizeof(SetRep));
   assert(S != NULL);
   S->nelems = 0;
   S->root = newTree();
   return S;
}
```
## AVL Trees
#
### Better Balanced Binary Trees
#
So far, we have seen …
- randomised trees … make poor performance unlikely
- occasional rebalance … fix balance periodically
- splay trees … reasonable amortized performance
- but all types still have O(n) worst case

Ideally, we want both average/worst case to be O(log n)
- AVL trees … fix imbalances as soon as they occur
- 2-3-4 trees … use varying-sized nodes to assist balance
- red-black trees … isomorphic to 2-3-4, but binary nodes

### AVL Trees
#
Invented by Georgy <b>A</b>delson-<b>V</b>elsky and Evgenii <b>L</b>andis   (1962)

Goal:
- tree remains reasonably well-balanced  O(log n)
- cost of fixing imbalance is relatively cheap

Approach:
- insertion (at leaves) may cause imbalance
- repair balance as soon as we notice imbalance
- repairs done locally, not by overall tree restructure

A tree is unbalanced when   abs(height(left)-height(right)) > 1

This can be repaired by rotation:
- if left subtree too deep, rotate right
- if right subtree too deep, rotate left

Problem: determining height/depth of subtrees is expensive
- need to traverse whole subtree to find longest path
> Solution: store balance data in each node  (either height or balance)
> - but extra effort needed to maintain this data on insertion

### AVL Trees examples
#
> Red numbers are height;   green numbers are balance

![](https://www.cse.unsw.edu.au/~cs2521/lecs/avl/Pics/avl1.png)

> How an unbalanced tree can be rebalanced

![](https://www.cse.unsw.edu.au/~cs2521/lecs/avl/Pics/avl2.png)

### AVL Insertion Algorithm
#
Implementation of AVL insertion
```
insertAVL(tree,item):
|  Input  tree, item
|  Output tree with item AVL-inserted
|
|  if tree is empty then
|     return new node containing item
|  else if item = data(tree) then
|     return tree
|  else
|  |  if item < data(tree) then
|  |     left(tree) = insertAVL(left(tree),item)
|  |  else if item > data(tree) then
|  |     right(tree) = insertAVL(right(tree),item)
|  |  end if
|  |  LHeight = height(left(tree))
|  |  RHeight = height(right(tree))
|  |  if (LHeight - RHeight) > 1 then
|  |     if item > data(left(tree)) then
|  |        left(tree) = rotateLeft(left(tree))
|  |     end if
|  |     tree=rotateRight(tree)
|  |  else if (RHeight - LHeight) > 1 then
|  |     if item < data(right(tree)) then
|  |        right(tree) = rotateRight(right(tree))
|  |     end if
|  |     tree=rotateLeft(tree)
|  |  end if
|  |  return tree
|  end if
```

### Maintaining Balance/Height
#
- Store height in nodes; update on insertion; compute balance

![](https://www.cse.unsw.edu.au/~cs2521/lecs/avl/Pics/avl3.png)

- If abs(balance) > 1 after updating, rebalance via rotation(s)

### Searching AVL Trees
#
Exactly the same as for regular BSTs.

![](https://www.cse.unsw.edu.au/~cs2521/lecs/avl/Pics/avl4.png)
[^1]

### Performance of AVL Trees
#
Analysis of AVL trees:
- trees are height-balanced; subtree depths differ by +/-1
- average/worst-case search performance of O(log n)
- require extra data to be stored in each node (efficiency)
- require extra data to be maintained during insertion
- may not be weight-balanced; subtree sizes may differ
![](https://www.cse.unsw.edu.au/~cs2521/lecs/avl/Pics/height-weight.png)

[don't forget to watch the other lecture: 2-3-4 trees and graph basics and graph representations]

#
[^1]: Height/balance measures are ignored