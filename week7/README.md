# First Lecture
## Directed/Weighted Graphs
### Generalising Graphs
Discussion so far has considered graphs as
- $V$ = set of vertices,   $E$ = set of edges
Real-world applications require more "precision"
- some edges are directional  (e.g. one-way streets)
- some edges have a cost  (e.g. distance, traffic)

> We need to consider directed graphs and weighted graphs
### Directed Graphs(Digraphs)

Directed graphs are ...
- graphs with V  vertices, E  edges (v,w)
- edge (v,w)  has source v  and destination w
- unlike undirected graphs, v → w   ≠   w → v

Example digraph:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/digraph0.png)

Some properties:
1. edges 1-2-3 form a cycle,   edges 1-3-4 do not  form a cycle
2. vertex 5 has a self-referencing edge (5,5)
3. vertices 0 and 1 reference each other, i.e. (0,1)  and (1,0)
4. there are no paths from 5 to any other nodes
5. paths from 0→5:  0-1-2-3-4-5,  0-1-4-5,  0-1-2-3-1-4-5

Terminology for digraphs …
> Directed path:   sequence of n ≥ 2 vertices v1 → v2 → … → vn
> - where ($v_i,v_{i+1}$) ∈ edges(G) for all $v_i,v_{i+1}$  in sequence
> If $v_1 = v_n$, we have a directed cycle
> Degree of vertex:   number of incident edges
> - outdegree:  deg(v) = number of edges of the form (v, _)
> - indegree:  deg-1(v) = number of edges of the form (_, v)

More terminology for digraphs …
1. Reachability:
- w is reachable from v if ∃ directed path v,…,w

2. Strong connectivity:
- every vertex is reachable from every other vertex

3. Directed acyclic graph (DAG):
- contains no directed cycles

### Digraph Representation
Similar set of choices as for undirectional graphs:
- array of edges   (directed)
- vertex-indexed adjacency matrix   (non-symmetric)
- vertex-indexed adjacency lists

> V vertices identified by 0 .. V-1
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/digraph-rep.png)

Example digraph and adjacency matrix representation:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/digraph1.png)

- Undirectional ⇒ symmetric matrix 
- Directional ⇒ non-symmetric matrix

> Maximum #edges in a digraph with V vertices: $V^2$
> Costs of representations:    (where degree deg(v) = #edges leaving v) [table in slide 8/19]

Overall, adjacency list representation is best
- real graphs tend to be sparse (large number of vertices, small average degree deg(v))
- algorithms frequently iterate over edges from v

### Weighted Graphs
Graphs so far have considered
- edge = an association between two vertices/nodes
- may be a precedence in the association (directed)

Some applications require us to consider
- a cost or weight of an association
- modelled by assigning values to edges (e.g. positive reals)

Weighted graphs are ...
- graphs with V  vertices, E  edges (s,t)
- each edge (s,t,w)  connects vertices s  and t  and has weight w [^1]

Example weighted graphs:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/wgraph0.png)

Example: major airline flight routes in Australia
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/flights.png)

> Representation:   edge = direct flight;   weight = approx flying time (hours)

Weights lead to minimisation-type questions, e.g.

1. Cheapest way to connect all vertices?
- a.k.a. minimum spanning tree problem
- assumes: edges are weighted and undirected
2. Cheapest way to get from A to B?
- a.k.a shortest path problem
- assumes: edge weights positive, directed or undirected

### Weighted Graph Representation
Weights can easily be added to:
- adjacency matrix representation   (0/1 → int or float)
- adjacency lists representation   (add int/float to list node)

> The edge list representation changes to list of (s,t,w) triples
> All representations can also work with directed edges

Weight values are determined by domain being modelled
- in some contexts weight could be zero or negative

1. Adjacency matrix representation with weights:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/adjmatrixw.png)

> Note: need distinguished value to indicate "no edge".

2. Adjacency lists representation with weights:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/adjlistsw.png)
> Note: if undirected, each edge appears twice with same weight

3. Edge array / edge list representation with weights:
![](http://www.cse.unsw.edu.au/~cs2521/20T2/lecs/graph-rep2/Pics/edgelistw.png)

>  not very efficient for use in processing algorithms, but does give a possible representation for min spanning trees or shortest paths

### Weighted Graph Implementation
Changes to preious grpah data structures to include weights:
```WGraph.h```

```
// edges are pairs of vertices (end-points) plus weight
typedef struct Edge {
   Vertex v;
   Vertex w;
   int    weight;
} Edge;

// returns weight, or 0 if vertices not adjacent
int adjacent(Graph, Vertex, Vertex);
```

> Note: here, we assume all weights are positive, but not required

1. WGraph.c  (assuming adjacency matrix representation)
```
typedef struct GraphRep {
   int **edges;  // adjacency matrix storing weights
                 // 0 if nodes not adjacent
   int   nV;     // #vertices
   int   nE;     // #edges
} GraphRep;

bool adjacent(Graph g, Vertex v, Vertex w) {
   assert(valid graph, valid vertices)
   return (g->edges[v][w] != 0);
}

void insertEdge(Graph g, Edge e) {
   assert(valid graph, valid edge)
   // edge e not already in graph
   if (g->edges[e.v][e.w] == 0) g->nE++;
   // may change weight of existing edge
   g->edges[e.v][e.w] = e.weight;
   g->edges[e.w][e.v] = e.weight;
}

void removeEdge(Graph g, Edge e) {
   assert(valid graph, valid edge)
   // edge e not in graph
   if (g->edges[e.v][e.w] == 0) return;
   g->edges[e.v][e.w] = 0;
   g->edges[e.w][e.v] = 0;
   g->nE--;
}
```

## Directed Graphs
### Directed Graphs (Digraphs)
Example digraph:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/digraphs/Pics/digraph0.png)
> definition in the previous topic

### Digraphs Applications
[slide 2/19: examples]

Problems to solve on digraphs:
- is there a directed path from s to t ?  (transitive closure)
- what is the shortest path from s to t ?  (shortest path)
- are all vertices mutually reachable?  (strong connectivity)
- how to organise a set of tasks?  (topological sort)
- which web pages are "important"?  (PageRank)
- how to build a web crawler?  (graph traversal)

### Transitive Closure
Problem: computing reachability    (```reachable(G,s,t)```)

Given a digraph G  it is potentially useful to know
- is vertex t  reachable from vertex s ?

Example applications:
- can I complete a schedule from the current state?
- is a malloc'd object being referenced by any pointer?

One possibility to implement a reachability check:
- use hasPath(G,s,t)   (itself implemented by DFS or BFS algorithm)
- feasible only if reachable(G,s,t)  is an infrequent operation

What about applications that frequently check reachability?
Would be very convenient/efficient to have:
```
reachable(G,s,t)  ≡  G.tc[s][t]
```

```tc[][]``` is called the transitive closure matrix
- ```tc[s][t]``` is 1 if there is a path from s  to t, 0 otherwise

> If V  is large, then this may not be feasible either.

The ```tc[][]``` matrix shows all directed paths in the graph
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/digraphs/Pics/tc.png)
> Question: how to build ```tc[][]``` from ```edges[][]```?

Goal: produce a matrix of reachability values

Observations:
- ∀s,t ∈ vertices(G):  (s,t) ∈ edges(G)  ⇒  tc[s][t] = 1
- ∀i,s,t ∈ vertices(G):  (s,i) ∈ edges(G) ∧ (i,t) ∈ edges(G)  ⇒  tc[s][t] = 1

In other words
- ```tc[s][t]=1``` if there is an edge from s  to t    (path of length 1)
- ```tc[s][t]=1``` if there is a path from s  to t of length 2    (s→i→t)

Extending the above observations gives ...

An algorithm to convert edges into a tc
```
makeTC(G):
|  tc[][] = edges[][]
|  for all i ∈ vertices(G) do
|  |  for all s ∈ vertices(G) do
|  |  |  for all t ∈ vertices(G) do
|  |  |  |  if tc[s][i]=1 ∧ tc[i][t]=1 then
|  |  |  |  |  tc[s][t]=1
|  |  |  |  end if
|  |  |  end for
|  |  end for
|  end for
```

This is known as Warshall's algorithm.

How it works …
1. After copying edges[][],  tc[s][t] is 1 if s→t  exists
2. After first iteration (i=0),  tc[s][t] is 1 if
  - either s→t  exists or s→0→t  exists
3. After second interation (i=1), tc[s][t] is 1 if any of
  - s→t   or   s→0→t   or   s→1→t   or   s→0→1→t   or   s→1→0→t
4. After the Vth iteration, tc[s][t] is 1 if
  - there is a directed path in the graph from s  to t

Tracing Warshall's algorithm on a simple graph:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/digraphs/Pics/tc-example.png)

Cost analysis:
- storage: additional V2 items  (but each item may be 1 bit)
- computation of transitive closure: V3
- computation of reachable(): O(1) after generating tc[][]

Amortisation: need many calls to ```reachable()``` to justify setup cost
Alternative: use DFS in each call to ```reachable()```

Cost analysis:
- storage: cost of Stack and Set during DFS calculation
- computation of reachable(): O(V2)   (for adjacency matrix)

### Digraph Traversal
Same algorithms as for undirected graphs:
```
depthFirst(G,v):
|  mark v as visited
|  for each (v,w) ∈ edges(G) do
|  |  if w has not been visited then
|  |  |  depthFirst(w)
|  |  end if
|  end for

breadthFirst(G,v):
|  enqueue v
|  while queue not empty do
|  |  curr=dequeue
|  |  if curr not already visited then
|  |  |  mark curr as visited
|  |  |  enqueue each w where (curr,w) ∈ edges(G)
|  |  end if
|  end while
```

### Example: Web Crawling
Goal: visit every page on the web 
Solution: breadth-first search with "implicit" graph

```
webCrawl(startingURL):
|  mark startingURL as alreadySeen
|  enqueue(Q,startingURL)
|  while not isEmpty(Q) do
|  |  currPage=dequeue(Q)
|  |  visit currPage
|  |  for each hyperLink on currPage do
|  |  |  if hyperLink not alreadySeen then
|  |  |     mark hyperLink as alreadySeen
|  |  |     enqueue(Q,hyperLink)
|  |  |  end if
|  |  end for
|  end while
```
- ```visit``` scans page and collects e.g. keywords and links

### PageRank
Goal: determine which Web pages are "important"

Approach: ignore page contents; focus on hyperlinks
- treat Web as graph: page = vertex, hyperlink = di-edge
- pages with many incoming hyperlinks are important
- need to computing "incoming degree" for vertices

> Problem: the Web is a very large graph
> - approx. 1010 pages,   1011 hyperlinks

Assume for the moment that we could build a graph …

Naive PageRank algorithm:
```
PageRank(myPage):
|  rank=0
|  for each page in the Web do
|  |  if linkExists(page,myPage) then
|  |     rank=rank+1
|  |  end if
|  end for
```
> Note: requires inbound link check   (normally, we check outbound)

- V = # pages in Web,   E = # hyperlinks in Web
> Costs for computing PageRank for each representation: [in slide 16/19]

Not feasible ...
- adjacency matrix ... V ≅ 1010 ⇒ matrix has 1020 cells
- adjacency list ... V  lists, each with ≅10 hyperlinks ⇒ 1011 list nodes

> So how to really do it?

The random web surfer strategy.

Each page typically has many outbound hyperlinks ...
- choose one at random, without a ```visited[]``` check
- follow link and repeat above process on destination page
If no visited check, need a way to (mostly) avoid loops
Important property of this strategy
- if we randomly follow links in the web …
- … more likely to re-discover pages with many inbound links

Random web surfer algorithm ...
```
curr=random page, prev=null
for a long time do
|  if curr not in array rank[] then
|     rank[curr]=0
|  end if
|  rank[curr]=rank[curr]+1
|  if random(0,100) < 85 then // with 85% chance ...
|     prev=curr               // ... keep crawling
|     curr=choose hyperlink from curr
|  else
|     curr=random page, not prev // avoid getting stuck
|     prev=null
|  end if
end for
```

Above is a very rough approximation to reality.

If you want the details ...
- The Anatomy of a Large-Scale Hypertextual Web Search Engine https://research.google/pubs/pub334/
- The PageRank Citation Ranking: Bringing Order to the Web http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf

And the background ...
- Authoritative Sources in a Hyperlinked Environment https://dl.acm.org/doi/pdf/10.1145/324133.324140

# Second Lecture
## Minimum Spanning Trees
### Minimum Spanning Trees
Reminder: Spanning tree ST of graph G=(V,E)
- spanning = all vertices, tree = no cycles
- ST  is a subgraph of G   (G'=(V,E') where E' ⊆ E)
- ST  is connected and acyclic

Minimum spanning tree MST of graph G
- MST  is a spanning tree of G
- sum of edge weights is no larger than any other ST

> Applications:
> - Computer networks, Electrical grids, Transportation networks …

Example:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/min-span-tree/Pics/mst-example.png)

Problem: how to (efficiently) find MST for graph G ?

One possible strategy:
1. generate all spanning trees
2. calculate total weight of each
3. MST = ST with lowest total weight

> Note that MST may not be unique
> e.g. if all edges have same weight, then all STs are MSTs

Brute force solution  (using generate-and-test strategy):
```
findMST(G):
|  Input  graph G
|  Output a minimum spanning tree of G
|
|  bestCost = ∞
|  for all spanning trees t of G do
|  |  if cost(t) < bestCost then
|  |     bestTree=t
|  |     bestCost=cost(t)
|  |  end if
|  end for
|  return bestTree
```

> Not useful in general because #spanning trees is potentially large 
> (e.g. $n^{n-2}$  for a complete graph with n  vertices)

Simplifying assumption:
- edges in G are not directed   (MST for digraphs is harder)

If edges are not weighted
- there is no real notion of minimum spanning tree

The MST algorithms given apply to
- weighted,  non-directional,  connected graphs


### Kruskal's Algorithm

One approach to computing MST for graph G with V  nodes:
1. start with empty MST
2. consider edges in increasing weight order
   - add edge if it does not form a cycle in MST
3. repeat until V-1 edges are added

Critical operations:
- iterating over edges in weight order
- checking for cycles in a graph

Execution trace of Kruskal's algorithm:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/min-span-tree/Pics/kruskal-trace.png)

Pseudocode:
```
KruskalMST(G):
|  Input  graph G with n nodes
|  Output a minimum spanning tree of G
|
|  MST=empty graph
|  sort edges(G) by weight
|  for each e ∈ sortedEdgeList do
|  |  MST = MST ∪ {e}  // add edge
|  |  if MST has a cyle then
|  |     MST = MST \ {e}  // drop edge 
|  |  end if
|  |  if MST has n-1 edges then
|  |     return MST
|  |  end if
|  end for
```
Rough time complexity analysis …
- sorting edge list is O(E·log E)
- at least V  iterations over sorted edges
- on each iteration …
   - getting next lowest cost edge is O(1)
   - checking whether adding it forms a cycle: cost = O(V2)

Possibilities for cycle checking:
- use DFS … too expensive?
- could use Union-Find data structure [^2]


### Prim's Algorithm

Another approach to computing MST for graph G=(V,E):

1. start from any vertex v and empty MST
2. choose edge not already in MST to add to MST;  must be:
   - incident on a vertex s  already connected to v  in MST
   - incident on a vertex t  not already connected to v  in MST
   - minimal weight of all such edges
3. repeat until MST covers all vertices

> Critical operations:
> - checking for vertex being connected in a graph
> - finding min weight edge in a set of edges

Execution trace of Prim's algorithm (starting at s=0):
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/min-span-tree/Pics/prim-trace.png)

Pseudocode:
```
PrimMST(G):
|  Input  graph G with n nodes
|  Output a minimum spanning tree of G
|
|  MST=empty graph
|  usedV={0}
|  unusedE=edges(g)
|  while |usedV| < n do
|  |  find e=(s,t,w) ∈ unusedE such that {
|  |     s ∈ usedV ∧ t ∉ usedV 
|  |       ∧ w is min weight of all such edges
|  |  }
|  |  MST = MST ∪ {e}
|  |  usedV = usedV ∪ {t}
|  |  unusedE = unusedE \ {e}
|  end while
|  return MST
```

> Critical operation:  finding best edge

Rough time complexity analysis …
- V  iterations of outer loop
- in each iteration, finding min-weighted edge …
   - with set of edges is O(E) ⇒ O(V·E) overall
   - with priority queue is O(log E) ⇒ O(V·log E) overall

> Note:
> - have seen stack-based (DFS) and queue-based (BFS) traversals
> - using a priority queue gives another non-recursive traversal

### Sidetrack: Priority Queues
Some applications of queues require
- items processed in order of "key"
- rather than in order of entry (FIFO — first in, first out)

Priority Queues (PQueues) provide this via:
- ```join```: insert item into PQueue (replacing enqueue)
- ```leave```: remove item with largest key (replacing dequeue)

> Will discuss priority queues in more detail in another lesson

### Other MST Algorithms
1. Boruvka's algorithm ... complexity O(E·log V)
- the oldest MST algorithm
- start with V separate components
- join components using min cost links
- continue until only a single component

2. Karger, Klein, and Tarjan ... complexity O(E)
- based on Boruvka, but non-deterministic
- randomly selects subset of edges to consider
- for the keen, here's the paper [^3]describing the algorithm

## Shortest Path Algorithms
### Shortest Path
Path = sequence of edges in graph G
- p = (v0,v1,weight1), (v1,v2,weight2), …, (vm-1,vm,weightm)

cost(path) = sum of edge weights along path

Shortest path between vertices s and t
- a simple path p(s,t) where s = first(p), t = last(p)
- no other simple path q(s,t) has cost(q) < cost(p)

> Assumptions: weighted digraph, no negative weights.
> Applications:  navigation,  routing in data networks,  …

Some variations on shortest path (SP) ...

1. Source-target SP problem
- shortest path from source vertex s  to target vertex t

2. Single-source SP problem
- set of shortest paths from source vertex s  to all other vertices

3. All-pairs SP problems
- set of shortest paths between all pairs of vertices s  and t


### Single - Source Shortest Path (SSSP)
Shortest paths from s  to all other vertices
- ```dist[]``` V-indexed array of cost of shortest path from s
- ```pred[]``` V-indexed array of predecessor in shortest path from s

Example:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/shortest-path/Pics/sssp.png)


### Edge Relaxation
Assume:  ```dist[]``` and ```pred[]``` as above
- but containing data for shortest paths discovered so far

If we have ...
- ```dist[v]``` is length of shortest known path from s  to v
- ```dist[w]``` is length of shortest known path from s  to w
- edge (v,w,weight)

Relaxation updates data for w  if we find a shorter path from s  to w :
- if  ```dist[v]+weight < dist[w]```  then
   - update  ```dist[w]←dist[v]+weight  and  pred[w]←v```

Relaxation along edge e = (v,w,3) :
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/shortest-path/Pics/relaxation.png)


### Dijkstra's Algorithm
One approach to solving single-source shortest path …
```
dist[]  // array of cost of shortest path from s
pred[]  // array of predecessor in shortest path from s
vSet    // vertices whose shortest path from s is unknown

dijkstraSSSP(G,source):
|  Input graph G, source node
|
|  initialise all dist[] to ∞
|  dist[source]=0
|  initialise all pred[] to -1
|  vSet=all vertices of G
|  while vSet ≠ ∅ do
|  |  find v ∈ vSet with minimum dist[v]
|  |  for each (v,w,weight) ∈ edges(G) do
|  |     relax along (v,w,weight)
|  |  end for
|  |  vSet=vSet \ {v}
|  end while
```

### Tracing Dijkstra's Algorithm
How Dijkstra's algorithm runs when source = 0:
![](https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/shortest-path/Pics/dijkstra-trace.png)

### Analysis of Dijkstra's Algorithm
Why Dijkstra's algorithm is correct ...

<b> Hypothesis: </b>

1. for visited s, dist[s] is shortest distance from source
2. (*) for unvisited t, dist[t] is shortest distance from source via visited nodes

Ultimately, all nodes are visited, so ...
- $∀$ v,  dist[v] is shortest distance from source

<b> Proof </b>
Base case: no visited nodes, dist[source]=0, dist[s]=∞ for all other nodes

Induction step:
1. If s  is unvisited node with minimum dist[s], then dist[s]  is shortest distance from source to s:
   - if ∃ shorter path via only visited nodes, then dist[s]  would have been updated when processing the predecessor of s on this path
   - if ∃ shorter path via an unvisited node u, then dist[u] < dist[s], which is impossible if s  has min distance of all unvisited nodes
2. This implies that (a) holds for s  after processing s
3. (2. (*) ) still holds for all unvisited nodes t  after processing s:
   - if ∃ shorter path via s  we would have just updated dist[t]
   - if ∃ shorter path without s  we would have found it previously

Time complexity analysis …

Each edge needs to be considered once ⇒ O(E).

Outer loop has O(V) iterations.

Implementing ```"find s ∈ vSet with minimum dist[s]"```
1. try all s∈vSet ⇒ cost = O(V) ⇒ overall cost = O(E + V2) = O(V2)
2. using a PQueue to implement extracting minimum
   - can improve overall cost to O(E + V·log V)

#
[^1]: Weights can be used in both directed and undirected graphs.
[^2]: (see Sedgewick Ch.1)
[^3]: https://cgi.cse.unsw.edu.au/~cs2521/20T2/lecs/min-span-tree/Karger95.pdf