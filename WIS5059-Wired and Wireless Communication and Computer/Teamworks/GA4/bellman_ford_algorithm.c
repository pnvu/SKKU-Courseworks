/*
Name: bellman_ford_algorithm.c
Description: The implementation of the Bellman-Ford algorithm in C.
Author: Phan Nguyen Vu
Date: 8th April, 2018
*/

#include <stdio.h>
#include <stdlib.h>

#define inf 999 // Assign a large value that describe infinity
#define N 6 // The number of nodes
char node[6] = {'u','v','w','x','y','z'};

// Recursive function to print out the shortest tree from node u to ith node
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
int printResults(int dist[], int n, int predecessor[])
{
    int src = 0;
    int i = 0;
    
    printf("Vertex\t  Distance\tPath");
    for (i = 1; i < N; i++)
    {
        printf("\n%c -> %c \t\t %d\t%c ", node[src], node[i], dist[i], node[src]);
        printPath(predecessor, i);
    }
}

void bellman_ford_algorithm(int c[N][N], int startNode){
	int d[N];	// Create an array to save all shortest paths from the the start node (node 0) --> node i
	int flag[N]; 	// An array created to avoid a node calculate the distance to itself
	int pre[N];	// Create an array to save predecessors
	
	// Initialize loop varibale
	int i = 0;
	int v = startNode;
	int w = startNode;	// The index of the node that among with the shortest path from source
	
	// Step 1: Initialize graph
	// Initialize value of dist and S
	for(i = 0; i<N; i++){
		pre[i] = -1;	// means null predecessor
		d[i] = inf;	// All vertices are initialized with a weight of infinity at the begining.
		flag[i] = 1;
	}
	
	d[v] = 0;	// Iteration 1: The weight is zero at the source
	
	// Step 2: Relax edges iteratively (iteration 1 to iteration (N-1))
	for (i=0; i<(N-1); i++){
		for(w=0; w<N; w++){
			// Turn off flag at v to avoid a node calculate the distance to itself
			flag[w] = 0;
			
			for (v=0; v<N; v++){
				if (flag[v]==1){
					if ((d[w] + c[w][v]) < d[v]){
						pre[v] = w;
						d[v] = d[w] + c[w][v];
					}
				}
			}
			
			// Turn on flag at v
			flag[w] = 1;
		}
	}
	printf("The entered graph: \n");
	for (i=0; i<N; i++){
		for (v=0; v<N; v++){
			if(c[i][v]==inf){
				printf("inf \t");
			}
			else{
				printf("%d \t", c[i][v]);
			}			
		}
		printf("\n");
	}
	
	printf("\nThe forwarding table and the shortest path from source node u: \n");
	printResults(d, N, pre);
}

int main(){
	// Initialize the graph
	int graph[N][N] = {{0,2,5,1,inf,inf},
	{2,0,3,2,inf,inf},
	{5,3,0,3,1,5},
	{1,2,3,0,1,inf},
	{inf,inf,1,1,0,2},
	{inf,inf,5,inf,2,0}};
	
	bellman_ford_algorithm(graph, 0);
	
	return 0;
}


