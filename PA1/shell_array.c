#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size)
{
	*size = 0;
	
	// Use fopen to open the file for read
	// Return NULL address if fopen fails
	FILE *file = fopen(filename, "rb");
	if(file == NULL)
	{
		return NULL;
	}

	// Use fseek to go to the end of the file
	// Check whether fseek fails
	// If fseek fails, fclose and return NULL address
	*size = fseek(file, 0, SEEK_END);
	if(*size != 0) 
	{
		fclose(file);
		return NULL;
	}
	
	// Use ftell to determine the size of the file
	// The number of integers is the file's size divided by 
	// Size of long
	*size = ftell(file) / sizeof(long);
	
	// Use fseek to go back to the begining of the file
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the array
	// If malloc fails, fclose and return false
	long *arr = malloc((sizeof(long) * (*size)));
	if(arr == NULL)
	{
		fclose(file);
		return NULL;
	}
    
	// Store Long integers into Array
	int i = 0;
	for(i = 0; i < *size; i++)
	{
		fread(&arr[i], sizeof(long), 1, file);
	}
	fclose(file);

	// Return address of Array
	return arr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
	int count;
	// fopen for write
	// If fopen fails, return 0
	FILE *file = fopen(filename, "wb");
	if(file == NULL)
	{
		return 0;
	}
	// Use fwrite to write the entire array to a file
	count = fwrite(array, sizeof(long), size, file);	
	
	// fclose
	fclose(file);	

	// Return Successful # of Long Integers stored
	return count;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
	// Gets Maximum K value within Array Size
	int k = 1;
  	while(k <= size)
  	{
    	k = (3 * k) + 1;
  	}
	k = (k - 1)/3; //Subtract While loop's extra K
	
	// Initiate SHELL SORT Algorithm
  	int j;
	int gap;
  	while(k > 0)
  	{
    	for(gap = k; gap < size; gap++)
    	{
      		long temp = array[gap]; 
      		(*n_comp)++; 			// Number of Comparisons
			
			for(j = gap; j >= k && array[j - k] > temp; j -= k)
			{
				array[j] = array[j - k];
			}
      		array[j] = temp;
    	}
		k = (k - 1)/3; // Decrement K = Gap
  	}
}
