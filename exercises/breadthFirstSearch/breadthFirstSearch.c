#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	// TODO
	// visited array filled with values of -1
	int *visited = malloc(GraphNumVertices(g) * sizeof(int));
	for (int i = 0; i < GraphNumVertices(g); i++) {
		visited[i] = -1;
	}
	// visited vertex src = src (as visited already)
	visited[src] = 1;
	// create new queue and queue src in it
	Queue bfs = QueueNew();
	QueueEnqueue(bfs, src);
	// while queueu is empty
	while (!(QueueIsEmpty(bfs))) {
		// dequeued item is curr
		Vertex curr = QueueDequeue(bfs);
		// print curr
		printf("%d ", curr);
		// check if adjacent and visited == -1; if yes then visited[] = 1 and
		// enqueue in the bfs queue
		for (Vertex i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, curr, i) && visited[i] == -1) {
				visited[i] = 1;
				QueueEnqueue(bfs, i);
			}
		}
	}
	// free queue
	QueueFree(bfs);
	free(visited);
}

