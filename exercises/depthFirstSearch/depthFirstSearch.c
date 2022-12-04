
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static void dfs(Graph g, int v, int *visited);

void depthFirstSearch(Graph g, int src) {
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	dfs(g, src, visited);
	free(visited);
}

static void dfs(Graph g, int v, int *visited) {
	printf("%d ", v);
	visited[v] = 1;
	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (GraphIsAdjacent(g, v, w) && !visited[w]) {
			dfs(g, w, visited);
		}
	}
}
