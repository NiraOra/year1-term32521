
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

static bool doHasCycle(Graph g, int v, int prev, bool *visited);

bool hasCycle(Graph g) {
	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));
	
	for (int v = 0; v < GraphNumVertices(g); v++) {
		if (!visited[v]) {
			if (doHasCycle(g, v, v, visited)) {
				free(visited);
				return true;
			}
		}
	}
	
	free(visited);
	return false;
}

static bool doHasCycle(Graph g, int v, int prev, bool *visited) {
	visited[v] = true;
	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (GraphIsAdjacent(g, v, w)) {
			if (visited[w]) {
				if (w != prev) {
					return true;
				}
			} else {
				if (doHasCycle(g, w, v, visited)) {
					return true;
				}
			}
		}
	}
	return false;
}