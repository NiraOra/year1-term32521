# First Lecture
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

# Second Lecture
## Basic Graph Algorithms
### Problems on Graphs
What kind of problems do we want to solve on/via graphs?
- how many connected components in the graph?
- is one vertex reachable from some other vertex? (path finding)
- what is the cheapest cost path from v to w?
- which vertices are reachable from v? (transitive closure)
- is there a cycle somewhere in the graph?
- is there a cycle that passes through all vertices? (circuit)
- is there a tree that links all vertices? (spanning tree)
- what is the minimum spanning tree?
- …
- can a graph be drawn in a plane with no crossing edges? (planar graphs)
- are two graphs "equivalent"? (isomorphism)

### Cycle Checking 
A graph has a cycle if
- it has a path of length > 2
- with start vertex src = end vertex dest
- and without using any edge more than once
- This graph has 3 distinct cycles:  0-1-2-0,  2-3-0-2,  0-1-2-3-0 [^2]
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/cycle-graph1.png)

Consider this graph:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/cycle-graph2.png)
<br>
This graph has many cycles e.g.  0-4-3-0,  2-4-5-2,  0-1-2-5-4-6-3-0,  ...

1. First attempt at checking for a cycle
```
hasCycle(G):
|  Input  graph G
|  Output true if G has a cycle, false otherwise
|
|  choose any vertex v ∈ G
|  return dfsCycleCheck(G,v)

dfsCycleCheck(G,v):
|  mark v as visited
|  for each (v,w) ∈ edges(G) do
|  |  if w has been visited then  // found cycle
|  |     return true
|  |  else if dfsCycleCheck(G,w) then
|  |     return true
|  end for
|  return false  // no cycle at v
```

The above algorithm has two bugs ...
- only one connected component is checked
- the loop ```for each (v,w) ∈ edges(G) do``` should exclude the neighbour of v  from which you just came, so as to prevent a single edge w-v  being classified as a cycle.

If we start from vertex 5 in the following graph, we don't find the cycle:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/cycle-graph3.png)

2. Version of cycle checking (in C) for one connected component:
```
bool dfsCycleCheck(Graph g, Vertex v, Vertex u) {
   visited[v] = true;
   for (Vertex w = 0; w < g->nV; w++) {
      if (adjacent(g, v, w)) {
         if (!visited[w]) {
            if (dfsCycleCheck(g, w, v))
               return true;
         }
         else if (w != u)
            return true;
      }
   }
   return false;
}
```

3. Wrapper to ensure that all connected components are checked:

```
Vertex *visited;

bool hasCycle(Graph g, Vertex s) {
   bool result = false;
   visited = calloc(g->nV,sizeof(int));
   for (int v = 0; v < g->nV; v++) {
      for (int i = 0; i < g->nV; i++)
         visited[i] = -1;
      if dfsCycleCheck(g, v, v)) {
         result = true;
         break;
      }
   }
   free(visited);
   return result;
}
```

### Connected Components
Consider these problems:
- how many connected subgraphs are there?
- are two vertices in the same connected subgraph?
<br>

Both of the above can be solved if we can
- build ```componentOf[]``` array, one element for each vertex v
- indicating which connected component v is in
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/components-ex.png)

1. Algorithm to assign vertices to connected components:
```
components(G):
|  Input  graph G
|  Output componentOf[] filled for all V
|
|  for all vertices v ∈ G do
|  |  componentOf[v]=-1
|  end for
|  compID=0  // component ID
|  for all vertices v ∈ G do
|  |  if componentOf[v]=-1 then
|  |     dfsComponent(G,v,compID)
|  |     compID=compID+1
|  |  end if
|  end for
```

2. 
DFS scan of one connected component
```
dfsComponent(G,v,id):
|  componentOf[v]=id
|  for each (v,w) ∈ edges(G) do
|     if componentOf[w]=-1 then
|        dfsComponent(G,w,id)
|     end if
|  end for
```

Consider an application where connectivity is critical
- we frequently ask questions of the kind above
- but we cannot afford to run ```components()``` each time

3. Add a new fields to the ```GraphRep``` structure:
```
typedef struct GraphRep *Graph;

struct GraphRep {
   ...
   int nC;  // # connected components
   int *cc; // which component each vertex is contained in
   ...      // i.e. array [0..nV-1] of 0..nC-1
}
```

4. With this structure, the above tasks become trivial:
```
// How many connected subgraphs are there?
int nConnected(Graph g) {
   return g->nC;
}
// Are two vertices in the same connected subgraph?
bool inSameComponent(Graph g, Vertex v, Vertex w) {
   return (g->cc[v] == g->cc[w]);
}
```
> But ... introduces overheads ... maintaining ```cc[],  nC```
<br>

Consider maintenance of such a graph representation:
- initially, ```nC = nV```   (because no edges)
- adding an edge may reduce ```nC``` (adding edge between v and w in different components)
- removing an edge may increase ```nC``` (removing edge between v and w in same component)
- ```cc[]``` can simplify path checking (ensure ```v,w``` are in same component before starting search)

> Additional cost amortised by lower cost for ```nConnected()``` and ```inSameComponent()```
> Is it simpler to run ```components()``` after each edge change?

### Hamiltonian Path and Circuit
Hamiltonian path problem [^3]:
- find a simple path connecting two vertices v,w  in graph G
- such that the path includes each vertex exactly once

If v = w, then we have a Hamiltonian circuit

Simple to state, but difficult to solve (NP-complete)

Many real-world applications require you to visit all vertices of a graph:
- Travelling salesman
- Bus routes
- …

Graph and some possible Hamiltonian paths (examples):
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/hamilton1.png)

Approach:
- generate all possible simple paths (using e.g. DFS)
- keep a counter of vertices visited in current path
- stop when find a path containing V vertices

Can be expressed via a recursive DFS algorithm
- similar to simple path finding approach, except
   - keeps track of path length; succeeds if length = v
   - resets "visited" marker after unsuccessful path

1. Algorithm for finding Hamiltonian path:

```
visited[] // array [0..nV-1] to keep track of visited vertices

hasHamiltonianPath(G,src,dest):
|  Input  graph G, plus src/dest vertices
|  Output true if Hamiltonian path src...dest,
|           false otherwise
|
|  for all vertices v ∈ G do
|     visited[v]=false
|  end for
|  return hamiltonR(G,src,dest,#vertices(G)-1)
```

2. Recursive component:

```
hamiltonR(G,v,dest,d):
|  Input G    graph
|        v    current vertex considered
|        dest destination vertex
|        d    distance "remaining" until path found
|
|  if v=dest then
|     if d=0 then return true else return false
|  else
|  |  visited[v]=true
|  |  for each (v,w) ∈ edges(G)  where not visited[w] do
|  |     if hamiltonR(G,w,dest,d-1) then
|  |        return true
|  |     end if
|  |  end for
|  end if
|  visited[v]=false           // reset visited mark
|  return false
```

<underline>Analysis:</underline> worst case requires (V-1)! paths to be examined

Consider a graph with isolated vertex and the rest fully-connected
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/hamilton-worst.png)

Checking ```hasHamiltonianPath(g,x,0)``` for any x
- requires us to consider every possible path
- e.g 1-2-3-4, 1-2-4-3, 1-3-2-4, 1-3-4-2, 1-4-2-3, …
- starting from any x, there are 3! paths ⇒ 4! total paths
- there is no path of length 5 in these (V-1)! possibilities

There is no known simpler algorithm for this task ⇒ NP-hard.

> Note, however, that the above case could be solved in constant time if we had a fast check for 0 and x being in the same connected component

### Euler path problem
Euler path problem [^4]:
- find a path connecting two vertices v,w in graph G
- such that the path includes each edge exactly once (note: the path does not have to be simple ⇒ can visit vertices more than once)

If v = w, the we have an Euler circuit
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/euler-path-tour.png)

Many real-world applications require you to visit all edges of a graph:
- Postman
- Garbage pickup
- …

One possible "brute-force" approach:
- check for each path if it's an Euler path
- would result in factorial time performance

Can develop a better algorithm by exploiting:
> Theorem.   A graph has an Euler circuit if and only if it is connected and all vertices have even degree
> Theorem.   A graph has a non-circuitous Euler path if and only if it is connected and exactly two vertices have odd degree

Graphs with an Euler path are often called Eulerian Graphs.
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-algos1/Pics/euler-graphs.png)

> Assume the existence of degree(g,v)

1. Algorithm to check whether a graph has an Euler path:
```
hasEulerPath(G,src,dest):
|  Input  graph G, vertices src,dest
|  Output true if G has Euler path from src to dest
|         false otherwise
|
|  if src≠dest then
|     if degree(G,src) is even ∨ degree(G,dest) is even then
|        return false
|     end if
|  end if
|  for all vertices v ∈ G do
|     if v≠src ∧ v≠dest ∧ degree(G,v) is odd then
|        return false
|     end if
|  end for
|  return true
```

<underline>Analysis of hasEulerPath algorithm:</underline>

- assume that connectivity is already checked
- assume that degree() is available via O(1) lookup
- single loop over all vertices ⇒ O(V)

If degree requires iteration over vertices
- cost to compute degree of a single vertex is O(V)
- overall cost is O(V2)

> problem tractable, even for large graphs (unlike Hamiltonian path problem) [^5]


#
[^1]: malloc but initialises values to zero
[^2]: "distinct" means the set  of vertices on the path, not the order
[^3]: Named after Irish mathematician/physicist/astronomer Sir William Hamilton (1805-1865)
[^4]: Problem named after Swiss mathematician, physicist, astronomer, logician and engineer Leonhard Euler (1707 - 1783; Based on a circuitous route via bridges in Konigsberg
[^5]: For the keen, a linear-time (in the number of edges, E) algorithm to compute an Euler path is described in [Sedgewick] Ch.17.7.

