
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	// TODO
	int *visited = malloc(GraphNumVertices(g) * sizeof(int));
	for (int i = 0; i < GraphNumVertices(g); i++) {
		visited[i] = -1;
	}
	visited[src] = src;
	bool found = false;
	Queue bfsQueue = QueueNew();
	QueueEnqueue(bfsQueue, src);
	while(!(QueueIsEmpty(bfsQueue))) {
		Vertex curr = QueueDequeue(bfsQueue);
		for (Vertex i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, curr, i) && visited[i] == -1) {
				visited[i] = curr;
				if (i == dest) {
					found = true;
				}
				QueueEnqueue(bfsQueue, i);
			}
		}
	}
	QueueFree(bfsQueue);

	if (found == false) {
		return 0;
	} else {
		int count = 0;
		Vertex curr = dest;
		while (curr != src) {
			count++;
			curr = visited[curr];
		}
		return count;
	}
}

