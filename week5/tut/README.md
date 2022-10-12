## Tute

- BST: any binary search capable tree
- AVL: automatically rebalances itself so that it has optimal height; rebalances by rotating (if there is a bad height difference then it rotates)
  
### 2 - 3 - 4 Trees
```
typedef struct Node *Link; // Links are pointers to nodes
typedef struct Node *Tree; // a Tree is a pointer to its root node

struct Node { int order; int data[3]; Link child[4]; };
```

check visualisation:
https://www.cs.usfca.edu/~galles/visualization/BTree.html (select Max degree of 4)

### Graph Representation
1. 
(i) is undirected
(ii) is directed 
[depends if the graph has arrows representing the links between the nodes (???? !!!)]