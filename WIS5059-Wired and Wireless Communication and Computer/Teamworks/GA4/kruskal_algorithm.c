/*
Name: kruskal_algorithm.c
Description: The implementation of the Kruskal algorithm to find out the spanning tree.
Author: Phan Nguyen Vu
Date: 9th April, 2018
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
int printResults(int n, int predecessor[])
{
    int src = 0;
    int i = 0;
    
    printf("Vertex\t \t Path");
    for (i = 1; i < N; i++)
    {
        printf("\n%c -> %c \t\t %c ", node[src], node[i], node[src]);
        printPath(predecessor, i);
    }
}

// Find the representative number
int find_set(int p[], int k){
	if (p[k] == -1){
		return k;
	}
	
	find_set(p, p[k]);
}

void kruskal_algorithm(int c[N][N]){
	// Variable to save the position of two vertex of an edge
	int src = 0;
	int des = 0;
	
	// Array that store predecessors
	int pre[N];	
	
	// Loop variables
	int i = 0;
	int j = 0;
	int v = 0;
	
	// Looping variable for union
	int u = 0;
	int duplicated_pre[N];
	int t = 0;
	
	// Variable to consider min edge every loop
	int min = inf;
	
	// Initialize values of pre to be -1
	for(i=0; i<N; i++){
		pre[i] = -1;
		duplicated_pre[i] = -1;
	}
	// Set the 0 elements in graph to be inf, because it affect the min operation
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			if(c[i][j] == 0){
				c[i][j] = inf;
			}
		}
	}
	
	// Begin the algorithm
	for(v=0; v<11; v++){
		min = inf;	// Reset min variable
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				if(min > c[i][j]){
					min = c[i][j];
					src = i;
					des = j;
				}
			}
		}
		// Check cirle
		if(find_set(pre, src) != find_set(pre, des)){
			// Union
			if (pre[des] != -1){
				u = des;
				while(u != -1){
					duplicated_pre[pre[u]] = u;
					// Update u
					u = pre[pre[u]];
				}
				
				// Update search tree in pre[]
				for(t=0; t<N; t++){
					pre[t] = duplicated_pre[t];
				}
			}
			
			// Upgrade tree
			pre[des] = src;
			duplicated_pre[des] = src;
		}
		
		c[src][des] = c[des][src] = inf;
	}
	
	printResults(N, pre);
}

int main(){
	int graph[N][N] = {{0, 7, inf, 5, inf, inf, inf}, 
	{7, 0, 8, 9, 7, inf, inf}, 
	{inf, 8, 0, inf, 5, inf, inf}, 
	{5, 9, inf, 0, 15, 6, inf}, 
	{inf, 7, 5, 15, 0, 8, 9},
	{inf, inf, inf, 6, 8, 0, 11}, 
	{inf, inf, inf, inf, 9, 11, 0}};
	
	kruskal_algorithm(graph);
	
	return 0;
}



