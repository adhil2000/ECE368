#include "grid.h"

// Constructs Grid based on the total # of Points
struct Grid* constructGrid(int points)
{
	// Allocate Required Memory
	struct Grid* fullGrid = malloc(sizeof(struct Grid));
	fullGrid->points = points;
	// Create an array of AdjNeighbor Lists. 
	fullGrid->list = malloc(points * sizeof(struct AdjNeighbor));

	// Create Nodes, Initialize as Empty
    int i = 0;
	while(i < points) 
	{
		fullGrid->list[i].head = NULL;
		i++;
	}

	return fullGrid;
}

// Adds Edges to the Undirected Graph
void addEdge(struct Grid* fullGrid, int fromNode, int dest, int weight)
{
	struct AdjNeighborNode* newNeighborNode = malloc(sizeof(struct AdjNeighborNode));
	newNeighborNode->dest = dest;
	newNeighborNode->weight = weight;
	newNeighborNode->next = fullGrid->list[fromNode].head;
	fullGrid->list[fromNode].head = newNeighborNode;
}

// Function to Create all Edges
void createEdges(struct Grid* fullGrid, short row, short col, int point, short *grid)
{
	int num = 0;
	while(num < point)
	{
		if((num % col) != 0)
		{
			addEdge(fullGrid, num, num - 1, grid[num - 1]);
		}
		if((num + 1) % col != 0)
		{
			addEdge(fullGrid, num, num + 1, grid[num + 1]);
		}
		if((num - col) >= 0)
		{
			addEdge(fullGrid, num, num - col, grid[num - col]);
		}
		if((num + row) < (row * col))
		{
			addEdge(fullGrid, num, num + col, grid[num + col]);
		}
		num++;
	}
	num = point - col;
	while(num < point)
	{
		addEdge(fullGrid, point, num, grid[num]);
		num++;
	}	
	
	free(grid);
}
