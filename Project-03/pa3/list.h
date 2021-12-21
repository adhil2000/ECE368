#ifndef __LIST__
#define __LIST__
#include <stdlib.h>

// A structure to represent a node in AdjNeighbor List.
struct AdjNeighborNode
{
	int dest; // Destination
	int weight; // Weight
	struct AdjNeighborNode* next; // next Pointer
};

// A structure to represent an AdjNeighbor List.
struct AdjNeighbor
{
	struct AdjNeighborNode *head; // Pointer to Head Node of List
};
#endif
