
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

// static bool checkDfsPath(Graph g, int v, int dest, int *visited);

void depthFirstSearch(Graph g, int src) {
	// TODO
	int totalVertices = GraphNumVertices(g);
	int *visited = calloc(totalVertices, sizeof(int));
	for (int i = 0; i < totalVertices; i++) {
		visited[i] = -1;
	}
	
	visited[src] = src;
	for (int i = 0; i < totalVertices; i++) {
		if (visited[i] != -1) {
			printf("%d ", visited[i]);
		}
	}
	printf("\n");
	free(visited);
	return;
}

/*
static bool checkDfsPath(Graph g, int v, int dest, int *visited) {
	for (int i = 0; i < GraphNumVertices(g); i++) {
		for (int j = 0; j < GraphNumVertices(g); j++) {
			if (GraphIsAdjacent(g, i, j)) {
				if (visited[j] == -1) {
					visited[j] = v;
					if (j = dest) {
						return true;
					} else if (checkDfsPath(g, j, dest)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
*/
