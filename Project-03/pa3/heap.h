#ifndef __HEAP__
#define __HEAP__
#include <stdlib.h>
#include <limits.h>

// Structure to represent a MinHeap Node called heapNode
struct heapNode
{
	int v; // Vertex
	int d; // Distance
} heapNode;

// Structure to represent a MinHeap
struct MinHeap
{
	int size; // # of heapNodes
	int capacity; // capacity
	struct heapNode **array; //array of heapNode paths
} MinHeap;

// heapNode Function Declarations
struct heapNode* newHeapNode(int v, int d);
void swapNode(struct heapNode** one, struct heapNode** two);
struct heapNode* extractMin(struct MinHeap* minheap, int **pos, int len);

// MinHeap Function Declarations
int isEmpty(struct MinHeap* minheap);
struct MinHeap* constructHeap(int size); 
int inHeap(struct MinHeap *minheap, int i);
void downwardHeapify(struct MinHeap* minheap, int i, int **pos, int len); 
void decreaseKey(struct MinHeap* minheap,int d, int pos, int dest, int **posArr);
#endif 
