
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static int doNumReachable(Graph g, int v, int *visited);

int numReachable(Graph g, int src) {
	// array of visited nodes
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	int result = doNumReachable(g, src, visited);
	// free array
	free(visited);
	return result;
}

static int doNumReachable(Graph g, int v, int *visited) {
	// visited src = 1
	visited[v] = 1;
	// begin with 1: for src 
	int result = 1;
	for (int w = 0; w < GraphNumVertices(g); w++) {
		// if visited and not in visited
		if (GraphIsAdjacent(g, v, w) && !visited[w]) {
			// add to result and continue till u reach
			// the true condition
			result += doNumReachable(g, w, visited);
		}
	}
	// return the result
	return result;
}
