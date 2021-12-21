#ifndef __GRID__
#define __GRID__
#include "list.h"

// A structure to represent an X * Y Grid. 
// Grid is an array of AdjNeighbor Lists.
struct Grid
{
	int points; // Total number of Points on the Grid
	struct AdjNeighbor* list; // AdjNeighbor List which contains, AdjNeighborNodes
} Grid;

struct Grid* constructGrid(int points);
void addEdge(struct Grid* fullGrid, int fromNode, int dest, int weight);
void createEdges(struct Grid* fullGrid, short row, short col, int point, short *grid);
#endif

