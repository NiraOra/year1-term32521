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

## Second Lecture
## 2 - 3 - 4 Trees
### Search Cost
Critical factor determining search cost in BSTs
- worst case: length of longest path
- average case: < average path length  (not all searches end at leaves)

Either way, path length (tree depth) is a critical factor
In a perfectly balanced tree, max path length = $log_{2}{n}$

The 2 in the path length is the branching factor  (binary search tree)

> What if branching factor > 2?
> - $log_{2}{4096} = 12,    log_{4}{4096} = 6,    log_{8}{4096} = 4$

### 2 - 3 - 4 Trees
```2-3-4 trees``` have three kinds of nodes
- 2-nodes, with two children (same as normal BSTs)
- 3-nodes, two values and three children
- 4-nodes, three values and four children
<br>
Example:

![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-tree.png)

2-3-4 trees are ordered similarly to BSTs
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-order.png)

In a balanced 2-3-4 tree:
  - all leaves are at same distance from the root

- 2-3-4 trees grow "upwards" from the leaves, via node splitting.

### Node Splitting
1. Insertion into a full node causes a split
- middle value propagated to parent node
- values in original node split across original node and new node
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-split.png)

2. Intermediate stage of insert-split:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-split1.png)

3. Searching in 2-3-4 trees:
```
Search(tree,item):
|  Input  tree, item
|  Output address of item if found in 2-3-4 tree
|         NULL otherwise
|
|  if tree is empty then
|     return NULL
|  else
|  |  scan tree.data to find i such that
|  |     tree.data[i-1] < item ≤ tree.data[i]
|  |  if item=tree.data[i] then   // item found
|  |     return address of tree.data[i]
|  |  else       // keep looking in relevant subtree
|  |     return Search(tree.child[i],item)
|  |  end if
|  end if
```

### Data Structure
1. Possible concrete 2-3-4 tree data structure:

```
typedef struct node {
   int          order;     // 2, 3 or 4
   int          data[3];   // items in node
   struct node *child[4];  // links to subtrees
} node;
```
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-node.png)

2. Finding which branch to follow
```
// n is a pointer to a (struct node)
int i;
for (i = 0; i < n->order-1; i++) {
   if (item <= n->data[i]) break;
}
// go to the ith subtree, unless item == n->data[i]
```
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-node1.png)

### Search Cost Analysis
2-3-4 tree searching cost analysis:
- as for other trees, worst case determined by height h
- 2-3-4 trees are always balanced ⇒ height is O(log n)
- worst case for height: all nodes are 2-nodes  (same case as for balanced BSTs, i.e. $h ≅ log_{2}{n}$)
- best case for height: all nodes are 4-nodes (balanced tree with branching factor 4, i.e. $h ≅ log_{4}{n}$)

### Insertion into 2-3-4 trees
<b>Insertion algorithm:</b>

- find leaf node where Item belongs (via search)
- if not full (i.e. order < 4)
  - insert Item in this node, order++
- if node is full (i.e. contains 3 items)
  - split into two 2-nodes as leaves
  - promote middle element to parent
  - insert item into appropriate leaf 2-node
  - if parent is a 4-node
    - continue split/promote upwards
  - if promote to root, and root is a 4-node
    - split root node and add new root

Illustration:
1. Insertion into a 2-node or 3-node:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-add.png)

2. Insertion into a 4-node (requires a split):
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-split.png)

3. Splitting the root:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-split-root.png)

4. Building a 2-3-4 tree … 7 insertions:
![](https://www.cse.unsw.edu.au/~cs2521/lecs/2-3-4/Pics/2-3-4-insert.png)

Insertion algorithm:
```
insert(tree,item):
|  Input  2-3-4 tree, item
|  Output tree with item inserted
|
|  if tree is empty then
|     return new node containing item
|  end if
|  node=Search(tree,item)
|  parent=parent of node
|  if node.order < 4 then
|     insert item into node
|     increment node.order
|  else
|  |  promote = node.data[1]     // middle value
|  |  nodeL   = new node containing data[0]
|  |  nodeR   = new node containing data[2]
|  |  delete node
|  |  if item < promote then
|  |     insert(nodeL,item)
|  |  else
|  |     insert(nodeR,item)
|  |  end if
|  |  insert(parent,promote)
|  |  while parent.order=4 do
|  |     continue promote/split upwards
|  |  end while
|  |  if parent is root ∧ parent.order=4 then
|  |     split root, making new root
|  |  end if
|  end if
```

Insertion cost  (remembering that 2-3-4 trees are balanced ⇒ h = log4n)
- search for leaf node in which to insert = O(log n)
- if node not full, insert item into node = O(1)
- if node full, promote middle, create two new nodes = O(1)
- if promotion propagates ...
  - best case: update parent = O(1)
  - worst case: propagate to root = O(log n)
> Overall insertion cost = O(log n)

### 2-3-4 Variations
Variations on 2-3-4 trees …

1. Variation #1: why stop at 4? why not 2-3-4-5 trees? or M-way trees?
- allow nodes to hold between M/2 and M-1 items
- if each node is a disk-page, then we have a B-tree (databases)
- for B-trees, depending on Item size, M > 100/200/400

2. Variation #2: don't have "variable-sized" nodes
- use standard BST nodes, augmented with one extra piece of data
- implement similar strategy as 2-3-4 trees → red-black trees.

## Graph Basics
### Graphs
Many applications require
- a collection of items (i.e. a set)
- relationships/connections between items

Examples:
- ```maps:``` items are cities, connections are roads
- ```web:``` items are pages, connections are hyperlinks

Collection types you're familiar with
- lists … linear sequence of items   (COMP1511)
- trees … branched hierachy of items   (Weeks 02/03)

> Graphs are more general … allow arbitrary connections

A graph $G = (V,E)$
- V  is a set of vertices
- E  is a set of edges   (subset of V×V )

Example:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/graph1.png)

Nodes are distinguished by a unique identifier
Edges may be (optionally) directed, labelled and/or weighted
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/graph-edges.png)

[real life example in slide 4]
> Notes: vertices are cities, edges are distance between cities, symmetric

Alternative representation of above:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/ausroads.png)

Questions we might ask about a graph:
- is there a way to get from item A to item B?
- what is the best way to get from A to B?
- which items are directly connected (A↔B)?

Graph algorithms are generally more complex than tree/list ones:
- no implicit order of items
- graphs may contain cycles
- concrete representation is less obvious
- algorithm complexity depends on connection complexity

### Properties of Graphs
> Terminology: |V| and |E| (cardinality) normally written just as V and E.

- A graph with V  vertices has at most V(V-1)/2 edges.

- The ratio $E:V$ can vary considerably.
  - if $E$ is closer to $V^2$, the graph is dense
  - if $E$ is closer to $V$, the graph is sparse
    - Example: web pages and hyperlinks

- Knowing whether a graph is sparse or dense is important
  - may affect choice of data structures to represent graph
  - may affect choice of algorithms to process graph

For an edge e that connects vertices v  and w
- v  and w are adjacent   (neighbours)
- e  is incident on both v  and w
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/degrees.png)

Degree of a vertex v
- number of edges incident on e

Synonyms:
- vertex = node
- edge = arc = link  
  > (Note: some people use arc for directed edges)

1. Path: a sequence of vertices where
  - each vertex has an edge to its predecessor
2. Cycle: a path where
  - last vertex in path is same as first vertex in path
3. Length of path or cycle = #edges
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/pc-graphs.png)

Connected graph
- there is a path from each vertex to every other vertex
- if a graph is not connected, it has ≥2 connected components

Complete graph KV
- there is an edge from each vertex to every other vertex
- in a complete graph, E = V(V-1)/2

![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/complete-graphs.png)

4. Tree: connected (sub)graph with no cycles
5. Spanning tree: tree containing all vertices
6. Clique: complete subgraph

Consider the following single graph:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/graph2.png)
> This graph has 25 vertices, 32 edges, and 4 connected components
<br>

> Note: The entire graph has no spanning tree; what is shown in green is a spanning tree of the third connected component

A spanning tree of connected graph G = (V,E)
- is a subgraph of G containing all of V
- and is a single tree (connected, no cycles)
A spanning forest of non-connected graph G = (V,E)
- is a subgraph of G containing all of V
- and is a set of trees (not connected, no cycles),
    - with one tree for each connected component

Can form spanning tree from graph by removing edges 
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/span-tree.png)
> Many possible spanning trees can be formed. Which is "best"?

Types:
1. Undirected graph
- edge(u,v) = edge(v,u),   no self-loops   (i.e. no edge(v,v))

2. Directed graph
- edge(u,v) ≠ edge(v,u),   can have self-loops   (i.e. edge(v,v))

Examples:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-basics/Pics/ud-graphs.png)

3. Weighted graph
- each edge has an associated value (weight)
- e.g. road map   (weights on edges are distances between cities)

4. Multi-graph
- allow multiple edges between two vertices
- e.g. function call graph   (f() calls g() in several places)

5. Labelled graph
- edges have associated labels
- can be used to add semantic information

## Graph Representation
### Graph Representations
Describing graphs:
- could describe via a diagram showing edges and vertices
- could describe by giving a list of edges
- assume we identify vertices by distinct integers

E.g. four representations of the same graph:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep/Pics/graph-reps.png)

We discuss three different graph data structures:
1. Array of edges
  - explicit representation of edges as (v,w) pairs
2. Adjacency matrix
  - edges defined by presence value in VxV matrix
3. Adjacency list
  - edges defined by entries in array of V lists

### Array-of-edges Representation
Edges are represented as an array of ```Edge``` values (= pairs of vertices)
- space efficient representation
- adding and deleting edges is slightly complex
- undirected: order of vertices in an ```Edge``` doesn't matter
- directed: order of vertices in an ```Edge``` encodes direction
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep/Pics/graph-array-edges.png)

> For simplicity, we always assume vertices to be numbered ```0..V-1```

1. Graph initialisation

```
newGraph(V):
|  Input  number of nodes V
|  Output new empty graph (no edges)
|
|  g.nV = V   // #vertices (numbered 0..V-1)
|  g.nE = 0   // #edges
|  allocate enough memory for g.edges[]
|  return g
```

Assumes ≅ 
```
struct Graph { 
  int nV; 
  int nE; 
  Edge edges[]; 
}
```

2. Edge insertion

```
insertEdge(g,(v,w)):
|  Input  graph g, edge (v,w)
|  Output graph g containing (v,w)
|
|  i=0
|  while i < g.nE ∧ g.edges[i] ≠ (v,w) do
|     i=i+1
|  end while
|  if i=g.nE then      // (v,w) not found
|     g.edges[i]=(v,w)
|     g.nE=g.nE+1
|  end if
```
[^2]

3. Edge removal
```
removeEdge(g,(v,w)):
|  Input  graph g, edge (v,w)
|  Output graph g without (v,w)
|
|  i=0
|  while i < g.nE ∧ g.edges[i] ≠ (v,w) do
|     i=i+1
|  end while
|  if i < g.nE then  // (v,w) found
|     g.edges[i]=g.edges[g.nE-1]
|         // replace by last edge in array
|     g.nE=g.nE-1
|  end if
```

4. Print a list of edges
```
showEdges(g):
|  Input graph g
|
|  for all i=0 to g.nE-1 do
|  |  (v,w)=g.edges[i]
|  |  print v"—"w
|  end for
```

### Array-of-edges Cost Analysis
Storage cost: O(E)

Cost of operations:
- initialisation: O(1)
- insert edge: O(E)    (need to check for edge in array)
- delete edge: O(E)    (need to find edge in edge array)

If array is full on insert
- allocate space for a bigger array, copy edges across ⇒ still O(E)

If we maintain edges in order
- use binary search to find edge ⇒ O(log E)

### Adjacency Matrix Representation
Edges represented by a V × V matrix
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep/Pics/adjmatrix.png)

Advantages
- easily implemented as 2-dimensional array
- can represent graphs, digraphs and weighted graphs
  - graphs: symmetric boolean matrix
  - digraphs: non-symmetric boolean matrix
  - weighted: non-symmetric matrix of weight values

Disadvantages:
- if few edges (sparse) ⇒ memory-inefficient    (O(V2) space)

1. Graph initialisation
```
newGraph(V):
|  Input  number of nodes V
|  Output new empty graph
|
|  g.nV = V   // #vertices (numbered 0..V-1)
|  g.nE = 0   // #edges
|  allocate memory for g.edges[][]
|  for all i,j=0..V-1 do
|     g.edges[i][j]=0   // false
|  end for
|  return g
```

2. Edge insertion
```
insertEdge(g,(v,w)):
|  Input  graph g, edge (v,w)
|  Output graph g containing (v,w)
|
|  if g.edges[v][w] = 0 then  // (v,w) not in graph
|     g.edges[v][w]=1    // set to true
|     g.edges[w][v]=1
|     g.nE=g.nE+1
|  end if
```

3. Edge removal
```
removeEdge(g,(v,w)):
|  Input  graph g, edge (v,w)
|  Output graph g without (v,w)
|
|  if g.edges[v][w] ≠ 0 then  // (v,w) in graph
|     g.edges[v][w]=0       // set to false
|     g.edges[w][v]=0
|     g.nE=g.nE-1
|  end if
```

4. Print a list of edges
```
showEdges(g):
|  Input graph g
|
|  for all i=0 to g.nV-1 do
|  |  for all j=i+1 to g.nV-1 do
|  |     if g.edges[i][j] ≠ 0 then
|  |        print i"—"j
|  |     end if
|  |  end for
|  end for
```

### Adjacency Matrix Cost Analysis 
Storage cost: O(V2)

> If the graph is sparse, most storage is wasted.

Cost of operations:
- initialisation: O(V2)   (initialise V×V matrix)
- insert edge: O(1)   (set two cells in matrix)
- delete edge: O(1)   (unset two cells in matrix)

A storage optimisation: store only top-right part of matrix.

![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep/Pics/graphRep2.png)

New storage cost: V-1 int ptrs + V(V+1)/2 ints   (but still O(V2))

Requires us to always use edges (v,w) such that v < w.

### Adjacency List Representation
For each vertex, store linked list of adjacent vertices:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep/Pics/adjlists.png)

Advantages
- relatively easy to implement in languages like C
- can represent graphs and digraphs
- memory efficient if E:V relatively small

Disadvantages:
- one graph has many possible representations (unless lists are ordered by same criterion e.g. ascending)

1. Graph initialisation
```
newGraph(V):
|  Input  number of nodes V
|  Output new empty graph
|
|  g.nV = V   // #vertices (numbered 0..V-1)
|  g.nE = 0   // #edges
|  allocate memory for g.edges[]
|  for all i=0..V-1 do
|     g.edges[i]=newList()  // empty list
|  end for
|  return g
```

2. Edge insertion:
```
insertEdge(g,(v,w)):
|  Input  graph g, edge (v,w)
|  Output graph g containing (v,w)
|
|  if not ListMember(g.edges[v],w) then
|     // (v,w) not in graph
|     ListInsert(g.edges[v],w)
|     ListInsert(g.edges[w],v)
|     g.nE=g.nE+1
|  end if
```

3. Edge removal:
```
removeEdge(g,(v,w)):
|  Input  graph g, edge (v,w)
|  Output graph g without (v,w)
|
|  if ListMember(g.edges[v],w) then
|     // (v,w) in graph
|     ListDelete(g.edges[v],w)
|     ListDelete(g.edges[w],v)
|     g.nE=g.nE-1
|  end if
```

4. Print a list of edges
```
showEdges(g):
|  Input graph g
|
|  for all i=0 to g.nV-1 do
|  |  for all v in g.edges[i] do
|  |     if i < v then
|  |        print i"—"v
|  |     end if
|  |  end for
|  end for
```

### Adjacency List Cost Analysis
Storage cost: O(V+E)

Cost of operations:
- initialisation: O(V)   (initialise V  lists)
- insert edge: O(V)   (need to check if vertex in list)
- delete edge: O(V)   (need to find vertex in list)

> Could sort vertex lists, but no benefit  (although no extra cost)

### Comparison of Graph Representations
[summary of operations in the last slide]


#
[^1]: Height/balance measures are ignored
[^2]: We "normalise" edges so that e.g  (v < w) in all (v,w)