#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hbt.h"
#include "avl_tree.h"

int main(int argc, char * * argv)
{
	// argv[0]: pa4
	// argv[1]: (-b or -e) use string compare strcmp
	// argv[2]: name of input file
	// argv[3]: name of output file
	
    if(argc > 4)
    {
        printf("%d\n", 0);
        return EXIT_FAILURE;
    }

    Tnode* bst = NULL;

	//AVL TREE IMPLEMENTATION
	//#######################
    if(strcmp(argv[1], "-b") == 0)
	{
		// Load File into AVL TREE
		bst = AVL_Load_From_File(argv[2], bst);
		if(bst == NULL)
		{
            printf("%d\n", -1);
			return EXIT_FAILURE;
		}
		
		// Save AVL TREE into File
        FILE* output = fopen(argv[3], "wb");
        if(output == NULL)
        {
            printf("%d\n", 0);
            return EXIT_FAILURE;
        }
        AVL_Save_To_File(output,bst);

        fclose(output);
        freeTree(bst);
        printf("%d\n", 1);
        return EXIT_SUCCESS;
    }

	//EVALUATION IMPLEMENTATION
	//#######################
    else if(strcmp(argv[1], "-e") == 0)
    {
		// Use fopen to open the file for read
        FILE* file = fopen(argv[2], "rb");
        if(file == NULL)
        {
            printf("%d,%d,%d\n", -1, 0, 0);
            return EXIT_FAILURE;
        }
		
		// Use fseek to go to the end of the file
		// Check whether fseek fails
        fseek(file, 0L, SEEK_END);
        
		// Use ftell to determine the size of the file
		int size = ftell(file) / (sizeof(int) + sizeof(char));

		// Use fseek to go back to the begining of the file
        fseek(file, 0, SEEK_SET);

        int *keys = malloc(size * sizeof(int));
        char *nodes = malloc(size * sizeof(char));

        int i;
        for(i = 0; i < size; i++)
        {
            fread(&keys[i], sizeof(int), 1, file);
            fread(&nodes[i], sizeof(char), 1, file);

            if(nodes[i] != 0 && nodes[i] != 1 && nodes[i] != 2 && nodes[i] != 3)
            {
                printf("%d,%d,%d\n", 0, 0, 0);
                
				free(keys);
                free(nodes);
                fclose(file);
                
				return EXIT_FAILURE;
            }
        }

        int index = 0;
        bst = createBST(keys, nodes, &index, size);
        // Print out Final Evaluation
		printf("%d,%d,%d\n", 1, isValidTree(bst), isHeightBalanced(bst));
        
		free(keys);
        free(nodes);
        freeTree(bst);
        fclose(file);
        return EXIT_SUCCESS;
    }
    else
    {
        printf("%d\n", 0);
        return EXIT_FAILURE;
    }
}
