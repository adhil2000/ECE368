#include "list.h"
#include "grid.h"
#include "heap.h"

// Loading, Writing, and Saving from Files
short* GRID_Load_From_File(FILE* file, short* row, short* col);
   int GRID_Save_To_File(char *filename, short row, short col, short *grid);
   int GRID_Time_Save_To_File(char *filename, short col, int *d);
   int GRID_Path_Save_To_File(char *filename, short row, short col, int *d, int *parent, int min, int len);

// Dijkstra Alogrithm, Grid, Paths, Edges
void dijkstra(struct Grid* fullGrid, int pred[], int d[], int fromNode);
void getPath(FILE* file, int row, int col, int parent[], int i, int *len);
 int findFastestPath(int d[], short col);
void freeGrid(struct Grid* fullGrid);

