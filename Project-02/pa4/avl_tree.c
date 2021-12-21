#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "avl_tree.h"

// Function to load tree from file
Tnode* AVL_Load_From_File(char *filename, Tnode* head)
{
    	Tnode* temp = NULL;

		// Use fopen to open the file for read
		// Return NULL address if fopen fails
        FILE* file = fopen(filename, "rb");
        if(file == NULL)
        {
            printf("%d\n", -1);
            return NULL;
        }
		// Use fseek to go to the end of the file
		// Check whether fseek fails
		// If fseek fails, fclose and return NULL address
        fseek(file, 0L, SEEK_END);
        int size = ftell(file) / (sizeof(int) + sizeof(char));
        
		// Use fseek to go back to the begining of the file
		fseek(file, 0, SEEK_SET);
        
        // Read integers + characters from file
        char chars;
		int ints;
		int i;
        for(i = 0; i < size; i++)
        {
            fread(&ints, sizeof(int), 1, file);
            fread(&chars, sizeof(char), 1, file);
            // Insert Operation
			if(chars == 'i')
            {
                temp = insertNode(head, ints);
				if(temp)
                {
                    head = temp;
                }
            }
			// Delete Operation
            else if(chars == 'd')
            {
                head = deleteNode(head, ints);
            }
			// Invalid Operation
            else 
            {
                freeTree(head);
                fclose(file);
                return NULL;
			}
		}
	
	// fclose and return head
	fclose(file);
	return head;
}

// Function to save to file
void AVL_Save_To_File(FILE* file, Tnode* node)
{
    char num;

    if(node == NULL)
    {
		return;
	}
	else
	{
        // Left and Right Child Exists
        if(node->right != NULL && node->left != NULL)
        {
            num = 3;
        }
		// Only Left Child Exists
        else if(node->right == NULL && node->left != NULL)
        {
            num = 2;
        }
		// Only Right Child Exists
        else if(node->right != NULL && node->left == NULL)
        {
            num = 1;
        }
		// No Children Exist
        else if(node->right == NULL && node->left == NULL)
        {
            num = 0;
        }
		
		// fwrite
        char logic  = num | 0;
        fwrite(&(node->key), sizeof(int), 1, file);
        fwrite(&logic, sizeof(char), 1, file);
		
		// Save to File
        AVL_Save_To_File(file, node->left);
        AVL_Save_To_File(file, node->right);
    }
}

// Function that returns bigger value
int getMax(int x, int y) 
{
	return (x > y)? x : y;
}

// Function that gets height of a node
int getHeight(Tnode* node)
{
	return (node == NULL)? -1 : node->height; 
}

// Function that gets the balance of a node
int getBalance(Tnode* node)
{
	return (node == NULL)? 0 : (getHeight(node->left) - getHeight(node->right));
}

// Function that calculates new height of a node
int getNewHeight(Tnode* node)
{
    return (getMax(getHeight(node->left), getHeight(node->right)) + 1);
}

// Function that frees memory of an entire tree
void freeTree(Tnode* node)
{
    if (node == NULL)
    {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// Function that creates a new node
Tnode* newNode(int key)
{
	// Create New Node
    Tnode* node = malloc(sizeof(struct _Tnode));
    node->key = key;
    node->right = NULL;
    node->left = NULL;
    node->height = 0;
    return node;
}

// Function that performs a Clockwise Rotation
Tnode* clockRight(Tnode* node)
{
	// Clockwise Rotation
    Tnode* newNode = node->left;
    node->left = newNode->right;
    newNode->right = node;
   
	// Get new height
	node->height = getNewHeight(node);
	newNode->height = getNewHeight(newNode);

	return newNode;
}

// Function that performs a Counter Clockwise Rotation
Tnode* clockLeft(Tnode* node)
{
	// Counter Clockwise Rotation
    Tnode* newNode = node->right;
    node->right = newNode->left;
    newNode->left = node;
	
	// Get new height
	node->height = getNewHeight(node);
	newNode->height = getNewHeight(newNode);
    
	return newNode;
}

// Function that balances a given Tree
Tnode* balanceTree(Tnode* node, int key)
{
    Tnode* newNode = NULL;
    Tnode* copy = NULL;
    Tnode* temp = NULL;
    
	// Get Balance of Node and Children
	int balance = getBalance(node);
    int right = getBalance(node->right);
    int left = getBalance(node->left);

	// Left Left Case
    if((balance > 1) && (left > -1))
	{
        copy = node;
        newNode = clockRight(node);
    }
	// Left Right Case
    else if((balance > 1) && (left < 0))
    {
        copy = node->left;
        node->left = clockLeft(node->left);
        temp = node;
        newNode = clockRight(node);
    }
	// Right Right Case
    else if((balance < -1) && (right > 0))
    {
        copy = node->right;
        node->right = clockRight(node->right);
        temp = node;
        newNode = clockLeft(node);
    }
	// Right Left Case
    else if((balance < -1) && (right < 1))
    {
        copy = node;
        newNode = clockLeft(node);
    }

	return (newNode != NULL)? newNode : node;
}

// Function that adds a Node to a Tree
Tnode* insertNode(Tnode* node, int key)
{
    if(node == NULL)
    {
        return newNode(key);
    }
	else if(key > node->key)
    {
        node->right = insertNode(node->right, key);
    }
    else 
    {
		// "Always go left when ecountering a Node with the same key"
        node->left = insertNode(node->left, key);
    }

	// Get New Height
    node->height = getNewHeight(node);
    
	// balance tree
    node = balanceTree(node, key);

    return node;
}

// Function that deletes a Node from a Tree
Tnode* deleteNode(Tnode* node, int key)
{
    Tnode* dNode = NULL;
    Tnode* prev = NULL;

    if(node == NULL)
    {
        return node;
    }
	// Delete Right Node
    if(key > node->key)
    {
        node->right = deleteNode(node->right, key);
        node->height = getNewHeight(node);
    }
	// Delete Left Node
    else if(key < node->key)
    {
        node->left = deleteNode(node->left, key);
        node->height = getNewHeight(node);
    }
	// Same Key Case
    else if(key == node->key)
    {
		// No Children
        if (node->right == NULL && node->left == NULL)
        {
            free(node);
            return NULL;
        }
		// Only Right Child Exists
        else if(node->right != NULL && node->left == NULL) 
        {
            dNode = node->right;
			// Delete Node
			if(dNode != NULL)
			{
				free(node);
				return dNode;
			}
        }
		// Only Left Child Exists
        else if(node->right == NULL && node->left != NULL) 
        {
            dNode = node->left;
			// Delete Node
			if(dNode != NULL)
			{
				free(node);
				return dNode;
			}
        }
		// Right and Left Child Exists
        else if(node->right != NULL && node->left != NULL)
        {
            prev = node->left;
            while(prev->right != NULL)
            {
                prev = prev->right;
            }

            node->key = prev->key;
            prev->key = key;
            node->left = deleteNode(node->left, key);
        }
		// Get New Height
        node->height = getNewHeight(node);
    }

    // balanceTree
    node = balanceTree(node, key);
    return node;
}

// Function that checks if a Tree is a BST
int isValidTree(Tnode* node)
{
	// is this a Valid Tree?
    if(node == NULL)
    {
        return 1;
    }

	if(((node->right != NULL) && (node->right->key < node->key)) || ((node->left != NULL) && (node->left->key > node->key)))
    {
        return 0;
    }

	return ((isValidTree(node->right)) == 1) || ((isValidTree(node->left)) == 1)? 1 : 0;	
}

// Function that checks if a Tree is Height Balanced
int isHeightBalanced(Tnode* node)
{
    if(node != NULL)
    {
    int b = getBalance(node);
	return ((b >= -1) && (b <= 1))? (isHeightBalanced(node->right) && isHeightBalanced(node->left)) : 0;
	}
	return 1;
}

// Function that creates a Binary Search Tree
Tnode* createBST(int* keys, char* nodes, int* i, int size)
{
    if(*i < size)
    {
        int x = ++*i;
		Tnode* node = newNode(keys[x]);
		switch(nodes[x])
		{
			// "A Numerical Value of 1 Means there is a Right Child"
        	case 1: node->right = createBST(keys, nodes, i, size);
            		node->height = getNewHeight(node);
					break;
			// "A Numerical Value of 2 Means there is a Left Child"
			case 2: node->left = createBST(keys, nodes, i, size);
            		node->height = getNewHeight(node);
					break;
			// "A Numerical Value of 3 Means there is a Right & Left Child"
        	case 3: node->left = createBST(keys, nodes, i, size);
            		node->height = getNewHeight(node);
            		node->right = createBST(keys, nodes, i, size);
            		node->height = getNewHeight(node);
       	}
        node->height = getNewHeight(node);
        return node;
    }
    else
    {
		// "A Numerical Value of 0 Means there are no children"
        return NULL;
    }
}
