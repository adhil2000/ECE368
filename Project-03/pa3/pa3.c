#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "dijkstra.h"

int main (int argc, char * * argv)
{
	// argv[0]: pa3
	// argv[1]: Binary Input File
	// argv[2]: Text Grid File
	// argv[3]: Fastest Time File
	// argv[4]: Fastest heapNode File
	
	if(argc != 5)
	{
		return EXIT_FAILURE; // Check if 5 Arguments are Passed
	}

	// Use fopen to open the file for read
	// Return NULL address if fopen fails
	FILE* file = fopen(argv[1], "rb");
    if(file == NULL)
    {
        return EXIT_FAILURE;
    }

    short row = 0; // #Rows in Grid
	short col = 0; // #Columns in Grid
    short *grid = GRID_Load_From_File(file, &row, &col);

    // Use fopen to open the file for write
	// Return NULL address if fopen fails
	if(GRID_Save_To_File(argv[2], row, col, grid) == -1)
	{
		return EXIT_FAILURE;
	}
    
	// Create Grid, using number of Points
	int point = row * col; 
	struct Grid* fullGrid = constructGrid(point + 1); 

	// Create Grid Edges
	createEdges(fullGrid, row, col, point, grid);

	int *d = malloc(point * sizeof(int*)); // Distance 
	int *parent = malloc(point * sizeof(int*)); // Paths

	dijkstra(fullGrid, parent, d, point);

	int min = findFastestPath(d, col); // findFastestPath

	// Find Fastest Times and Save to File
	if(GRID_Time_Save_To_File(argv[3], col, d) == -1)
	{
		return EXIT_FAILURE;
	}

	int len = 0;
	int temp = min;
	for(temp = min; parent[temp] != -1; temp = parent[temp])
	{
		len++;
	}

	// Find Fastest Path and Save to File
	if(GRID_Path_Save_To_File(argv[4], row, col, d, parent, min, len) == -1)
	{
		return EXIT_FAILURE;
	}

	freeGrid(fullGrid); // Free Grid

    return EXIT_SUCCESS;
}
