#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "dijkstra.h"

// Function to Load the Grid from Binary file
short* GRID_Load_From_File(FILE* file, short* row, short* col)
{
	// Attain Grid Dimensions
    short x = 0; 
    short y = 0;
    fread(&x, sizeof(short), 1, file);
    fread(&y, sizeof(short), 1, file);

	// Allocate Space based on Grid X * Y Dimensions
    short *grid = malloc((x * y) * sizeof(short *));

	// Store all other values in Grid
    int i = 0;
    short temp = 0;
	while (i < x * y)
    {
        fread(&temp, sizeof(short), 1, file);
        grid[i] = temp;
		i++;
    }

	// Update row and col
    *row = x;
    *col = y;

	fclose(file);
    return grid;
}

// Function to save Grid to File in .txt format
int GRID_Save_To_File(char *filename, short row, short col, short *grid)
{
    int i = 0;
    int counter = 0;

	FILE* file = fopen(filename, "w");
	if(file == NULL)
	{
		return -1;
	}

	// "The first line is printed with the format %hd %hd\n "
    fprintf(file,"%hd %hd\n", row, col);

	// "There should be m lines. Each line should print n shorts"
	while(i < row * col)
    {
		// "There should be a newline character (’\n’) immediately after the last short in each line (row)."
        if(counter == col)
        {
            fprintf(file, "\n");
            counter = 0;
        }
		// "There should be a space (’ ’) character between a pair of consecutive short’s."
        if(counter % col != 0)
        {
            fprintf(file, " ");
        }
		// "each short is printed with the format %hd ""
        fprintf(file, "%hd", grid[i]);
        counter++;
		i++;
    }
	// "There should not be a space character after the last short in a line."
    fprintf(file, "\n");
	fclose(file);
	return 1;
}

// Function to save fastest time to file file
int GRID_Time_Save_To_File(char *filename, short col, int *d)
{
	int n = 0;
	FILE* file = fopen(filename, "wb");

	if(file == NULL)
	{
		return -1;
	}
	// "The file first stores the number of entry locations in the top row"
	fwrite(&col, sizeof(short), 1, file);

	// "The file next stores n int."
	while(n < col)
	{
		fwrite(&d[n], sizeof(int), 1, file);
		n++;
	}

	fclose(file);
	return 1;
}

// Function to write the fastest path to file file
int GRID_Path_Save_To_File(char *filename, short row, short col, int *d, int *parent, int min, int len)
{
	FILE* file = fopen(filename, "wb");
	if(file == NULL)
	{
		return -1;
	}

	// "The file first stores the fastest time it would take for 
	// a visitor to enter at a location in the top row of the input grid
	// and exit at a location in the bottom row of the input grid."
	fwrite(&d[min], sizeof(int), 1, file);
	// "Then, we store in the file an int for the number of locations that constitute the path."
	fwrite(&len, sizeof(int), 1, file);
	// write the path
	getPath(file, row, col, parent, min, &len);

	free(d);
	free(parent);
	fclose(file);
	return 1;
}

// Dijkstra Algorithm
void dijkstra(struct Grid* fullGrid, int pred[], int d[], int fromNode)
{
	int i = 0;
	int dest; 
	int v; 
	int size = fullGrid->points;
	int *pos = malloc(size * sizeof(int));

	struct MinHeap* minheap = constructHeap(size);

	while(i < size)
	{
		d[i] = minheap->capacity;
		pred[i] = -1;
		pos[i] = i;
		i++;
	}

	d[fromNode] = 0;
	minheap->array[fromNode]->d = 0;
	pos[minheap->array[fromNode]->v] = 0;
	pos[minheap->array[0]->v] = fromNode;

	swapNode(&minheap->array[fromNode], &minheap->array[0]); 

	struct heapNode* min = NULL;
	struct AdjNeighbor* adj = NULL;
	struct AdjNeighborNode* edge = NULL;

	// DIJKSTRA Algorithm 
	while(!(isEmpty(minheap))) 
	{
		min = extractMin(minheap, &pos, size); 
		v = min->v; 
		adj = fullGrid->list;

		for (edge = adj[v].head; edge != NULL; edge = edge->next)
		{
			dest = edge->dest; 
			if(inHeap(minheap, pos[dest]) && (d[dest] > edge->weight + d[v]))
			{
				d[dest] = edge->weight + d[v];
				decreaseKey(minheap, d[dest], pos[dest], dest, &pos);
				pred[dest] = v; 
			}
		}
		free(min);
	}

    free(minheap->array);
    free(minheap);
	free(pos);
}

// Function to get desired Path
void getPath(FILE* file, int row, int col, int parent[], int i, int *len)
{
    if(parent[i] != - 1) 
	{
		short tempRow = i / col;
		int count = i;
		for(count = i; (count > col) && (count - col > -1); count -= col) {}
		short tempCol = (count == col) ? 0 : count;

		fwrite(&tempRow, sizeof(short), 1, file);
		fwrite(&tempCol, sizeof(short), 1, file);

    	getPath(file, row, col, parent, parent[i], len);
	}
}

// Function to find the fastest path to heapNode
int findFastestPath(int d[], short col) {
	int i = 1;
	int min = 0;
	
	while(i < col) 
	{
		min = (d[i] < d[min]) ? i : min;
		i++;
	}

	return min;
}

// Function to free constructed grid
void freeGrid(struct Grid* fullGrid) {
	int i = 0;
	while(i < fullGrid->points)
    {
        struct AdjNeighborNode *node = fullGrid->list[i].head;
		struct AdjNeighborNode *next;

        while(node != NULL)
        {
              next = node;
              node = node->next;
              free(next);
        }
		i++;
    }

	free(fullGrid->list);
	free(fullGrid);
}
