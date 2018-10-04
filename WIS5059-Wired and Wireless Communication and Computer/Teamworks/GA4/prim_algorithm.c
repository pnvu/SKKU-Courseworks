/*
Name: prim_algorithm.c
Description: The implementation of Prim algorithm in C
Author: Phan Nguyen Vu
Date: 10th April, 2018
*/

#include <stdio.h>
#include <stdlib.h>

#define inf 999 // Assign a large value that describe infinity
#define N 7 // The number of nodes
const int node[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

void printPath(int predecessor[], int j)
{
    // Base Case : If j is source
    if (predecessor[j]==-1){
    	return;
    }
         
    printPath(predecessor, predecessor[j]);
 
    printf("--> %c", node[j]);
}
 
// Print the path and the distance from node u to ith node
int printResults(int n, int predecessor[], int startNode)
{
    int src = startNode;
    int i = 0;
    
    printf("Vertex\t  \t Path");
    for (i = 0; i < N; i++)
    {
    	if (i != src){
    		printf("\n%c -> %c \t\t %c ", node[src], node[i], node[src]);
        	printPath(predecessor, i);
    	}        
    }
}

void prim_algorithm(int c[N][N], int startNode){
	int key[N];	// Store the distances between the current node to its neighbors
	int pi[N];	// Store nodes that are visited 
	int pre[N];	// Store the predecessor of nodes that form the tree
	int src[N];	// Store the source of visited nodes, support for key[N]
	int u = 0;	// The position of the current node
	
	// Looping variables
	int i = 0;
	int j = 0;
	
	// Consider minimum value and its index
	int min = inf;
	int idx = 0;
	
	// Initialize the algorithm
	for (i=0; i<N; i++){
		key[i] = inf;
		pi[i] = 1;	// mean pi = NULL (no nodes have been visited)
		pre[i] = -1;		
	}
	
	// Begin the algorithm
	u = startNode;
	pi[u] = 0;	// Put node u into array that save visited node
	for (i=0; i<N; i++){
		key[i] = c[u][i];
		src[i] = u;
		
		if (pi[i] == 1){
			if (min > key[i]){
				min = key[i];
				idx = i;
				pre[i] = u;
			}
		}
	}
	u = idx;
	pi[u] = 0;
	
	// Iterate the rest N - 1 nodes in graph
	for (j=0; j<N-2; j++){
		min = inf;
		for (i=0; i<N; i++){
			if (pi[i] == 1){
				if(key[i] > c[u][i]){
					key[i] = c[u][i];
					src[i] = u;
				}
				// Check min
				if (min > key[i]){
					min = key[i];
					idx = i;
					pre[i] = src[i];
				}
			}
		}
		u = idx;
		pi[u] = 0;
	}
	
	printResults(N, pre, startNode);
}

int main(){
	int graph[N][N] = {{0, 7, inf, 5, inf, inf, inf}, 
	{7, 0, 8, 9, 7, inf, inf}, 
	{inf, 8, 0, inf, 5, inf, inf}, 
	{5, 9, inf, 0, 15, 6, inf}, 
	{inf, 7, 5, 15, 0, 8, 9},
	{inf, inf, inf, 6, 8, 0, 11}, 
	{inf, inf, inf, inf, 9, 11, 0}};
	
	prim_algorithm(graph, 0);
	
	return 0;
}


