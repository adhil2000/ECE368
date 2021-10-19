
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_list.h"
#include "shell_array.h"
#include "list_of_list.h"

int main (int argc, char * * argv)
{
	// argv[0]: pa1
	// argv[1]: -a use string compare strcmp
	// argv[2]: name of input file
	// argv[3]: name of output file
	
	if(argc != 4) // Check if 4 Arguments are Passed
	{
		return EXIT_FAILURE;
	}

	//SHELLSORT FOR ARRAY
	//###################
	if(strcmp(argv[1], "-a") == 0)
	{
	int size;				// Array Size
	long n_comp = NULL;		// N_comp
	long *array = NULL;		// Array Initialized
	int newsize;		
	array = Array_Load_From_File(argv[2], &size); // Load file into array
	
	if(array != NULL) // Check if Array has Elements
	{
		if(size == 0) // Check Size
		{
			newsize = Array_Save_To_File(argv[3], array, size); // Successful Saves
			n_comp = 0; // Set n_comp to 0
		}
		else
		{
			Array_Shellsort(array, size, &n_comp); // Run SHELLSORT ALGORITHM
			newsize = Array_Save_To_File(argv[3], array, size); // Successful Saves
		}
		printf("%ld\n", n_comp); // Print Numbers Compared 
		
		if(newsize != size) // Check if all Numbers where compared
		{
			return EXIT_FAILURE;
		}
	}
	if(array == NULL) // Exit if Array is NULL
	{
		return EXIT_FAILURE;
	}
		free(array); // Free Memory
	}	
	//###################

	//SHELLSORT FOR Linked List
	//#########################
	if(strcmp(argv[1], "-l") == 0)
	{
		long n_comp = NULL;
		Node *head = List_Load_From_File(argv[2]);

		head = List_Shellsort(head, &n_comp);

		List_Save_To_File(argv[3], head);
		printf("%ld\n", n_comp);
		
		// free nodes
		Node *current = head;
		Node *next = NULL;
		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}
			head = NULL;
	}
	
	return EXIT_SUCCESS;
}
