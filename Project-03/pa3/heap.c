#include "heap.h"

// Function to create a new heapNode
struct heapNode* newHeapNode(int v, int d)
{
	struct heapNode* newHeapNode = malloc(sizeof(struct heapNode));
	newHeapNode->v = v;
	newHeapNode->d = d;

	return newHeapNode;
}

// Function to swap two nodes
void swapNode(struct heapNode** one, struct heapNode** two)
{
	struct heapNode *oldNode = *one;
	*one = *two;
	*two = oldNode;
}

// Basic extractMin Function
struct heapNode* extractMin(struct MinHeap* minheap, int **pos, int len)
{
	if(!isEmpty(minheap))
	{
		struct heapNode* root = minheap->array[0];
		struct heapNode* lastNode = minheap->array[(minheap->size) - 1];
		minheap->array[0] = lastNode;
		(*pos)[root->v] = (minheap->size) - 1;
		(*pos)[lastNode->v] = 0;
		(minheap->size)--;

		// Heapify
		downwardHeapify(minheap, 0, pos, len);
		return root;
	}

	return NULL;
}

// Function to check if MinHeap is empty
int isEmpty(struct MinHeap* minheap)
{
	return (minheap->size == 0) ? 1 : 0;
}
// Function to construct a minHeap
struct MinHeap* constructHeap(int size) 
{
	struct MinHeap* minheap = malloc(sizeof(struct MinHeap));
	minheap->array = malloc(size * sizeof(struct heapNode*));
	minheap->capacity = INT_MAX; // Should I use SHRT_MAX or INT_MAX, Hmmm...
	minheap->size = 0;

	int i = 0;
	while(i < size)
	{
		minheap->array[i] = newHeapNode(i, minheap->capacity);
		(minheap->size)++;
		i++;
	}

	return minheap;
}

// Function to check if in Heap
int inHeap(struct MinHeap *minheap, int i)
{
	return (i < minheap->size) ? 1 : 0;
}

// Basic downwardHeapify Function
void downwardHeapify(struct MinHeap* minheap, int i, int **pos, int len) 
{
	int min = i; 
	int left = (min * 2) + 1; // left child
	int right = (min * 2) + 2; // right child

	int shortestDist = minheap->array[min]->d;
	if(left < minheap->size)
	{
		min = (minheap->array[left]->d < shortestDist) ? left : i;
	}

	int newShortestDist = minheap->array[min]->d;
	if(right < minheap->size)
	{
		min = (minheap->array[right]->d < newShortestDist) ? right : min;
	}

	if(min != i)
	{
		// Typecast was needed
		(*pos)[(minheap->array[min])->v] = i;
		(*pos)[(minheap->array[i])->v] = min;

		swapNode(&minheap->array[min], &minheap->array[i]);
		downwardHeapify(minheap, min, pos, len);
	}
}

// Basic decreaseKey Function
void decreaseKey(struct MinHeap* minheap,int d, int pos, int dest, int **posArr)
{
	int parent; 
	int i = pos;

	minheap->array[i]->d = d;

	for(i = pos; i > 0; i = (i - 1) / 2)
	{
		parent = (i - 1) / 2;

		int child_dist = minheap->array[i]->d;
		int parent_dist = minheap->array[parent]->d;
		
		if(child_dist < parent_dist) 
		{
			(*posArr)[(minheap->array[i]->v)] = parent;
			(*posArr)[(minheap->array[parent]->v)] = i;

			swapNode(&minheap->array[i], &minheap->array[parent]);

		}
	}
}
