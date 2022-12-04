
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

static int *giveDistance(Graph g, int src);
static int *bfsSearch(Graph g, int val);

int numWithin(Graph g, int src, int dist) {
	// TODO
	// create a distances array: to indicate how much distance it
	// takes for src to reach other vertices
	int *distances = giveDistance(g, src);

	// counter to add and see how many vertices fall under the given distance 
	// ie increment 
	int count = 0;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (distances[i] >= 0 && distances[i] <= dist) {
			count++;
		}
	}
	// free the distances array and return the count
	free(distances);
	return count;
}

static int *giveDistance(Graph g, int src) {
	// predecessor array from bfs search
	int *predArr = bfsSearch(g, src);
	// make a new array for distances
	int *distances = malloc(GraphNumVertices(g) * sizeof(int));

	// for given vertices:
	// 1. if predecessor array gives -1: end, so distance is -1 since
	// nothing is accessing 
	// 2. Otherwise, count the distance using the access of predecessor array
	// , where the end distance is the distance[i]
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (predArr[i] == -1) {
			distances[i] = -1;
		} else {
			int distance = 0;
			int curr = i;
			while (curr != src) {
				distance++;
				curr = predArr[curr];
			}
			distances[i] = distance;
		}
	}
	// free predecessor array and return this distance array
	free(predArr);
	return distances;
}
static int *bfsSearch(Graph g, int val) {
	// malloc space for predecessor array
	int *pred = malloc(GraphNumVertices(g) * sizeof(int));
	// fill the predecessor array values with -1
	for (int i = 0; i < GraphNumVertices(g); i++) {
		pred[i] = -1; 
	}
	// the predecessor of the beginning value is itself
	pred[val] = val;
	// create a new queue and enqueue the src in it
	Queue bfs = QueueNew();
	QueueEnqueue(bfs, val);
	// check if the queued values (curr) is is adjacent and present in 
	// predecessor array; if yes then set predecessor array and queue it
	while (!(QueueIsEmpty(bfs))) {
		int curr = QueueDequeue(bfs);
		for (int temp = 0; temp < GraphNumVertices(g); temp++) {
			if (GraphIsAdjacent(g, curr, temp) && pred[temp] == -1) {
				pred[temp] = curr;
				QueueEnqueue(bfs, temp);
			}
		}
	}
	// free queue and return predecessor array
	QueueFree(bfs);
	return pred;
}


