## First Lecture
## Graph ADT

(usually refer to Graph ADT (Adjacency Matrix) or Graph ADT (Adjacency Lists))
- node cannot have more than one tree (age is relationship between two nodes)

### Graph ADT
- Data:  set of edges,  set of vertices

- Operations:
  - building: create graph, add edge
  - deleting: remove edge, drop whole graph
  - scanning: check if graph contains a given edge

Things to note:
  - set of vertices is fixed when graph initialised
  - we treat vertices as ints, but could be arbitrary Items

> Will use this ADT as a basis for building more complex operations later.

- Graph ADT interface  ```Graph.h```

```
// graph representation is hidden
typedef struct GraphRep *Graph;

// vertices denoted by integers 0..N-1
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge { Vertex v; Vertex w; } Edge;

// operations on graphs
Graph newGraph(int V);  // new graph with V vertices
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
      // is there an edge between two vertices?
void  freeGraph(Graph);
```

### Graph ADT (Array of Edges)

1. Implementation of GraphRep (array-of-edges representation)

```
typedef struct GraphRep {
   Edge *edges; // array of edges
   int   nV;    // #vertices (numbered 0..nV-1)
   int   nE;    // #edges
   int   n;     // size of edge array
} GraphRep;
```
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-adt/Pics/graph-array-edges-rep.png)

> How much is enough? … No more than V(V-1)/2 … Much less in practice (sparse graph)

2. Implementation of graph initialisation (array-of-edges)

```
Graph newGraph(int V) {
   assert(V >= 0);
   Graph g = malloc(sizeof(GraphRep));   
   assert(g != NULL);
   g->nV = V; g->nE = 0;
   // allocate enough memory for edges
   g->n = Enough;
   g->edges = malloc(g->n*sizeof(Edge));
   assert(g->edges != NULL);
   return g;
}
```

3. Some useful utility functions:

```
// check if two edges are equal
bool eq(Edge e1, Edge e2) {
   return ( (e1.v == e2.v && e1.w == e2.w)
            || (e1.v == e2.w && e1.w == e2.v) );
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) {
   return (g != NULL && v >= 0 && v < g->nV);
}

// check if an edge is valid in a graph
bool validE(Graph g, Edge e) {
   return (g != NULL && validV(e.v) && validV(e.w));
}
```

4. Implementation of edge insertion (array-of-edges)

```
void insertEdge(Graph g, Edge e) {
   // ensure that g exists and array of edges isn't full
   assert(g != NULL && g->nE < g->n && isValidE(g,e));
   int i = 0;  // can't define in for (...)
   for (i = 0; i < g->nE; i++)
       if (eq(e,g->edges[i])) break;
   if (i == g->nE)  // edge e not found
      g->edges[g->nE++] = e;
}
```

5. Implementation of edge removal (array-of-edges)

```
void removeEdge(Graph g, Edge e) {
   // ensure that g exists
   assert(g != NULL && validE(g,e));
   int i = 0;
   while (i < g->nE && !eq(e,g->edges[i]))
      i++;
   if (i < g->nE)  // edge e found
      g->edges[i] = g->edges[--g->nE];
}
```
6. Implementation of edge check (array-of-edges)

```
bool adjacent(Graph g, Vertex x, Vertex y) {
   assert(g != NULL && validV(g,x) && validV(g,y));
   Edge e;
   e.v = x; e.w = y;
   for (int i = 0; i < g->nE; i++) {
      if (eq(e,g->edges[i]))  // edge found
         return true;
   }
   return false;  // edge not found
}
```

7. Re-implementation of edge insertion (array-of-edges)

```
void insertEdge(Graph g, Edge e) {
   // ensure that g exists
   assert(g != NULL && validE(g,e));
   int i = 0;
   for (i = 0; i < g->nE; i++)
       if (eq(e,g->edges[i])) break;
   if (i == g->nE) { // edge e not found
      if (g->n == g->nE) {  // array full; expand
         g->edges = realloc(g->edges, 2*g->n);
         assert(g->edges != NULL);
         g->n = 2*g->n;
      }
      g->edges[g->nE++] = e;
   }
}
```

8. Implementation of graph removal (array-of-edges)

```
void freeGraph(Graph g) {
   assert(g != NULL);
   free(g->edges);  // free array of edges
   free(g);         // remove Graph object
}
```

### Graph ADT (Adjacency Matrix)
1. Implementation of ```GraphRep``` (adjacency-matrix representation)

```
typedef struct GraphRep {
   int  **edges; // adjacency matrix
   int    nV;    // #vertices
   int    nE;    // #edges
} GraphRep;
```
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-adt/Pics/graphRep.png)

2. Implementation of graph initialisation (adjacency-matrix)

```
Graph newGraph(int V) {
   assert(V >= 0);
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;  g->nE = 0;
   // allocate array of pointers to rows
   g->edges = malloc(V * sizeof(int *));
   assert(g->edges != NULL);
   // allocate memory for each column and initialise with 0
   for (int i = 0; i < V; i++) {                                            
      g->edges[i] = calloc(V, sizeof(int));
      assert(g->edges[i] != NULL);
   }
   return g;
}
```

- Standard library function ```calloc(size_t nelems, size_t nbytes)``` [^1]
  - allocates a memory block of size nelems*nbytes
  - and sets all bytes in that block to zero

3. Implementation of edge insertion (adjacency-matrix)

```
void insertEdge(Graph g, Edge e) {
   assert(g != NULL && validE(g,e));

   if (!g->edges[e.v][e.w]) {  // edge e not in graph
      g->edges[e.v][e.w] = 1;
      g->edges[e.w][e.v] = 1;
      g->nE++;
   }
}
```

4. Implementation of edge removal (adjacency-matrix)
```
void removeEdge(Graph g, Edge e) {
   assert(g != NULL && validE(g,e));

   if (g->edges[e.v][e.w]) {   // edge e in graph
      g->edges[e.v][e.w] = 0;
      g->edges[e.w][e.v] = 0;
      g->nE--;
   }
}
```

5. Implementation of edge check (adjacency matrix)
```
bool adjacent(Graph g, Vertex x, Vertex y) {
   assert(g != NULL && validV(g,x) && validV(g,y));

   return (g->edges[x][y] != 0);
}
```
> Note: all operations, except creation, are O(1)

6. Implementation of graph removal (adjacency matrix)

```
void freeGraph(Graph g) {
   assert(g != NULL);
   for (int i = 0; i < g->nV; i++)
      // free one row of matrix
      free(g->edges[i]);
   free(g->edges);  // free array of row pointers
   free(g);         // remove Graph object
}
```

### Graph ADT (Adjacency Lists)

1. Implementation of GraphRep (adjacency-lists representation)
```
typedef struct GraphRep {
   Node **edges;  // array of lists
   int    nV;     // #vertices
   int    nE;     // #edges
} GraphRep;
```
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-adt/Pics/graphRep3.png)

2. Assume that we have a linked list implementation
```
typedef struct Node {
   Vertex v;
   struct Node *next;
} Node;
```

- with operations like  ```inLL,  insertLL,  deleteLL,  freeLL,```   e.g.
```
bool inLL(Node *L, Vertex v) {
   while (L != NULL) {
      if (L->v == v) return true;
      L = L->next;
   }
   return false;
}
```

3. Implementation of graph initialisation (adjacency lists)
```
Graph newGraph(int V) {
   assert(V >= 0);
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;  g->nE = 0;
   // allocate memory for array of lists
   g->edges = malloc(V * sizeof(Node *));
   assert(g->edges != NULL);
   for (int i = 0; i < V; i++)
      g->edges[i] = NULL;
   return g;
}
```

4. Implementation of edge insertion/removal (adjacency lists)

```
void insertEdge(Graph g, Edge e) {
   assert(g != NULL && validE(g,e));
   if (!inLL(g->edges[e.v], e.w)) {  // edge e not in graph
      g->edges[e.v] = insertLL(g->edges[e.v], e.w);
      g->edges[e.w] = insertLL(g->edges[e.w], e.v);
      g->nE++;
   }
}
void removeEdge(Graph g, Edge e) {
   assert(g != NULL && validE(g,e));
   if (inLL(g->edges[e.v], e.w)) {  // edge e in graph
      g->edges[e.v] = deleteLL(g->edges[e.v], e.w);
      g->edges[e.w] = deleteLL(g->edges[e.w], e.v);
      g->nE--;
   }
}
```

5. Implementation of edge check (adjacency lists)
```
bool adjacent(Graph g, Vertex x, Vertex y) {
   assert(g != NULL && validV(g,x) && validV(g,y));
   
   return inLL(g->edges[x], y);
}
```
> Note: all operations, except creation, are O(E)

6. Implementation of graph removal (adjacency lists)

```
void freeGraph(Graph g) {
   assert(g != NULL);
   for (int i = 0; i < g->nV; i++)
      freeLL(g->edges[i]); // free one list
   free(g->edges);  // free array of list pointers
   free(g);         // remove Graph object
}
```

### Example: Graph ADT Client
A program that uses the graph ADT to
  - build the graph depicted below
  - print all the nodes that are incident to vertex 1 in ascending order
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-adt/Pics/graph4.png)

```
#include <stdio.h>
#include "Graph.h"

#define NODES 4
#define NODE_OF_INTEREST 1

int main(void) {
   Graph g = newGraph(NODES);
   Edge e;

   while (scanf("%d %d", &(e.v), &(e.w)) == 2)
      insertEdge(g,e);

   for (Vertex v = 0; v < NODES; v++) {
      if (adjacent(g, v, NODE_OF_INTEREST))
         printf("%d\n", v);
   }

   freeGraph(g);
   return 0;
}
```

## Graph Traversal
### Problems on Graphs
What kind of problems do we want to solve on graphs?
- is the graph fully-connected?
- can we remove an edge and keep it fully-connected?
- is one vertex reachable starting from some other vertex?
- what is the cheapest cost path from v to w ?
- which vertices are reachable from v ? (transitive closure)
- is there a cycle that passes through all vertices? (circuit)
- is there a tree that links all vertices? (spanning tree)
- what is the minimum spanning tree?

While these problems are expressed as problems on graphs, they are interesting because many real world problems can be mapped onto graphs, and the solutions to the above could then be applied in solving them.

### Graph Traversal
Many of the above problems can be solved by
- systematic exploration of a graph, via the edges

Algorithms for this typically require us to remember
- what vertices we have already visited
- the path we followed while visiting them

Since many graph search algorithms are recursive
- above information needs to be stored globally
- and updated by individual calls to the recursive function

Systematic exploration like this is called traversal or search.

Consider two related problems on graphs ...
- is there a path between two given vertices (src,dest )?
- what is the sequence of vertices from src to dest ?

An approach to solving this problem:
- examine vertices adjacent to src
- if any of them is dest, then done
- otherwise try vertices two edges from src
- repeat looking further and further from src

The above summarises one form of graph traversal.

There are two strategies for graph traversal/search ...

1. Depth-first search  (DFS)
- favours following path rather than neighbours
- can be implemented recursively or iteratively (via stack)
- full traversal produces a depth-first spanning tree

2. Breadth-first search  (BFS)
- favours neighbours rather than path following
- can be implemented iteratively (via queue)
- full traversal produces a breadth-first spanning tree

> The method on the previous slide is effectively breadth-first traversal.

Comparison of BFS/DFS search for checking ```hasPath(a,h)```?
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/graph-search-bfs-dfs.png)
Both approaches ignore some edges by remembering previously visited vertices.

A spanning tree of a graph
- includes all vertices, using a subset of edges, without cycles

Consider the following graph:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/graph0.png)

> Consider how DFS and BFS could produce its spanning tree

Spanning tree resulting from DFS ... 
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/dfs-tree.png)

> Note: choose neighbours in ascending order

Spanning tree resulting from BFS ... 
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/bfs-tree.png)

> Note: choose neighbours in ascending order

### Depth-first Search

1. Depth-first search can be described recursively as:
```
visited = {}

depthFirst(G,v):
|  visited = visited ∪ {v}
|  for all (v,w) ∈ edges(G) do
|  |  if w ∉ visited then
|  |  |  depthFirst(G,w)
|  |  end if
|  end for
```

- The recursion induces backtracking

2. Recursive DFS path checking

```
visited = {}

hasPath(G,src,dest):
|  Input  graph G, vertices src,dest
|  Output true if there is a path from src to dest,
|         false otherwise
|
|  return dfsPathCheck(G,src,dest)
```

Requires wrapper around recursive function ```dfsPathCheck()```

3. Recursive function for path checking

```
dfsPathCheck(G,v,dest):
|  visited = visited ∪ {v}
|  for all (v,w) ∈ edges(G) do
|  |  if w=dest then   // found edge to dest
|  |     return true
|  |  else if w ∉ visited then
|  |     if dfsPathCheck(G,w,dest) then
|  |        return true  // found path via w to dest
|  |     end if
|  |  end if
|  end for
|  return false  // no path from v to dest
```

### Depth-first Traversal Example
Tracing the execution of ```dfsPathCheck(G,0,5)``` on:
<br>
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/dfsPathCheck.png)

> Reminder: we consider neighbours in ascending order
> Clearly does not find the shortest path

### DFS Cost Analysis
Cost analysis:
- each vertex visited at most once $\rightarrow$ cost = $O(V)$
- visit all edges incident on visited vertices $\rightarrow$ cost = O(E)
  - assuming an adjacency list representation

Time complexity of DFS: $O(V+E)$   (adjacency list representation)

### Path Finding 
Knowing whether a path exists can be useful

Knowing what the path is, is even more useful

Strategy:
- record the previously visited node as we search
- so that we can then trace path (backwards) through graph

> Requires a global array (not a set):
> ```visited[v]``` contains vertex w from which we reached v

1. Function to find path src→dest and print it

```
visited[] // store previously visited node
          // for each vertex 0..nV-1

findPath(G,src,dest):
|  Input graph G, vertices src,dest
|
|  for all vertices v∈G do
|     visited[v]=-1
|  end for
|  visited[src]=src  // starting node of the path
|  if dfsPathCheck(G,src,dest) then
|  |  // show path in dest..src order
|  |  v=dest
|  |  while v≠src do
|  |     print v"-"
|  |     v=visited[v]
|  |  end while
|  |  print src
|  end if
```

2. Recursive function to build path in ```visited[]```
```
dfsPathCheck(G,v,dest):
|  for all (v,w) ∈ edges(G) do
|  |  if visited[w] = -1 then
|  |     visited[w] = v
|  |     if w = dest then  // found edge from v to dest
|  |        return true
|  |     else if dfsPathCheck(G,w,dest) then
|  |        return true  // found path via w to dest
|  |     end if
|  |  end if
|  end for
|  return false  // no path from v to dest
```

The ```visited[]``` array after ```dfsPathCheck(G,0,7)``` succeeds
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/dfsFindPath.png)

3. DFS can also be described non-recursively (via a stack):

```
visited[] // store previously visited node
          // for each vertex 0..nV-1

findPathDFS(G,src,dest):
|  Input graph G, vertices src,dest
|
|  for all vertices v∈G do
|     visited[v]=-1
|  end for
|  found=false
|  visited[src]=src
|  push src onto new stack S
|  while not found ∧ S is not empty do
|  |  pop v from S
|  |  if v=dest then
|  |     found=true
|  |  else
|  |  |  for each (v,w)∈edges(G) with visited[w]=-1 do
|  |  |     visited[w]=v
|  |  |     push w onto S
|  |  |  end for
|  |  end if
|  end while
|  if found then
|     display path in dest..src order
|  end if
```

Uses standard stack operations ... Time complexity is still $O(V+E)$

### Breadth-first Search
Basic approach to breadth-first search (BFS):
- visit and mark current vertex
- visit all neighbours of current vertex
- then consider neighbours of neighbours

> Notes:
> tricky to describe recursively
> but a minor variation on non-recursive DFS search works 
> ⇒ switch the stack for a queue

1. BFS path finding algorithm:

```
visited[] // store previously visited node
          // for each vertex 0..nV-1

findPathBFS(G,src,dest):
|  Input  graph G, vertices src,dest
|
|  for all vertices v∈G do
|     visited[v]=-1
|  end for
|  found=false
|  visited[src]=src
|  enqueue src into queue Q
|  while not found ∧ Q is not empty do
|  |  dequeue v from Q
|  |  if v=dest then
|  |     found=true
|  |  else
|  |  |  for each (v,w) ∈ edges(G) with visited[w]=-1 do
|  |  |     visited[w]=v
|  |  |     enqueue w into Q
|  |  |  end for
|  |  end if
|  end while
|  if found then
|     display path in dest..src order
|  end if
```

> Uses standard queue operations   (enqueue, dequeue, check if empty)

- The ```visited[]``` array after ```findPathBFS(G,0,7)``` succeeds
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-traversal/Pics/findPathBFS.png)

<b>Time complexity of BFS: $O(V+E)$ (same as DFS)</b>

- BFS finds a "shortest" path
  - based on minimum # edges between src and dest.
  - stops with first-found path, if there are multiple ones

- In many applications, edges are weighted and we want path
  - based on minimum sum-of-weights along path src .. dest



#
[^1]: malloc but initialises values to zero
