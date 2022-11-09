## Tute

- reachable -> follow the path to get to a node from one node

- write a function that takes a Graph and start vertex (path)

pseudocode

```
struct graph {
  int n;       // number of vertices 
  int **edges; // edges
}

typedef struct graph *Graph;

int visited[n] = {0};

// recursive
Set reachable(Graph g, Vertex src) {
  // for loop, loop through all svertices and check if visited

  visited[src] = 1;
  Set s;
  set_add(s, src); // adding the first vertex into the set
  for (int i = 0; i < g->n; i++) {
    if (edges[src][i] && !(visited[i])) {
      set_combine(s, reachable(g, i));
    }

  }
  return s;
}

// iteratively
// imagine if you have stack operations:
// stack_push(Stack s, int n);
// int n = stack_pop(Stack s);
// stack_empty(Stack s); // returns empty if stack is empty

Set reachable(Graph g, Vertex src) {
  Set set;
  Stack s;
  stack_push(s, src);
  // visited[src] = 1;
  while (!(stack_empty(s))) {
    curr = stack_pop(s);
    set_add(set, curr);
    visited[curr] = 1;
    for (int i = 0; i < g->n; i++) {
      if (edges[src][i] && !(visited[i])) {
        stack_push(s, i);
        // to make sure nothing goes in the set twice
        // visited[curr] = 1;
      }
    }
  }
  return set;
}

// to search nodes in order (DFS but priority on smallest 
// node)
Set reachable(Graph g, Vertex src) {
  Set set;
  Stack s;
  stack_push(s, src);
  while (!(stack_empty(s))) {
    curr = stack_pop(s);
    set_add(set, curr);
    visited[curr] = 1;
    for (int i = g->n - 1; i >= 0; i--) {
      if (edges[src][i] && !(visited[i])) {
        stack_push(s, i);
      }
    }
  }
  return set;
}

// breadth first search
// queue
Set reachable(Graph g, Vertex src) {
  Set set;
  Queue q;
  QueueEnqueue(q, src);
  while (!(QueueIsEmpty(q))) {
    curr = QueueDequeue(q);
    QueueEnqueue(set, curr);
    visited[curr] = 1;
    for (int i = 0; i < g->n; i++) {
      if (edges[src][i] && !(visited[i])) {
        QueueEnqueue(q, i);
      }
    }
  }
  return set;
}
```

- Dijkstra's algorithm -> shorter path

```
visited[n] = { 0 };
distance[n] = { -1 }; // -1 if not visited yet

priority_queue pq; // smallest is first; priority number in ascending --> which is just the cumulative distance

// also have a predecessor to keep track

void dijkstra(Graph g, int src) {
  priority_queue pq;
  pq.push(src, 0);
  int curr;
  int dist;
  int distance[n];

  while (!(priority_queue_is_empty(pq))) {
    // if already visited, ignore it
    if (visited[curr]) {
      continue;
    } 
    diancent[curr] = dist;
    
    (curr, dist) = pq.pop(pq);
    visited[curr] = 1;

    for (int i = 0; i < g->n; i++) {
      if (g->edges[src][i] && !(visited[i])) {
        pq.push(i, dist + g->edges[src][i]);
      }
    }
  }

}


```

- kruskal's algorithmL find minimum spanning tree
```
MSTree kruskalFindMST(Graph g) {
	MSTree mst = GraphNew(); // MST initially empty
	Edge eList[g->nV]; // sorted array of edges
	edges(eList, g->nE, g);
	sortEdgeList(eList, g->nE);
	for (int i = 0; mst->nE < g->nV - 1; i++) {
		Edge e = eList[i];
		GraphAddEdge(mst, e);
		if (GraphHasCycle(mst)) GraphRemoveEdge(mst, e);
	}
	return mst;
}
```