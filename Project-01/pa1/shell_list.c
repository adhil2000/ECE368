#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_list.h"
//#####################################################################
Node *List_Load_From_File(char *filename)
{	
	int size;
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
	size = fseek(file, 0, SEEK_END);
	if(size != 0) 
	{
		fclose(file);
		return NULL;
	}

	// Use ftell to determine the size of the file
	// The number of integers is the file's size divided by 
	// Size of long
	size = ftell(file) / sizeof(long);
	
	// Use fseek to go back to the begining of the file
	fseek(file, 0, SEEK_SET);

	//STORE FILE AS LINKED LIST
	Node* temp = malloc(sizeof(Node));
	Node* head = NULL;
	Node* tail = NULL;

	while(fread(temp, sizeof(long), 1, file))
	{
		if(head == NULL)
		{
			head = malloc(sizeof(Node));
			tail = head;
		}
		else 
		{
			tail->next = malloc(sizeof(Node));
			tail = tail->next;
		}
		tail->value = temp->value;
		tail->next = NULL;
	}
	free(temp);
	// fclose file, Return address of head
	fclose(file);
	return head;
}
//#####################################################################

int List_Save_To_File(char *filename, Node *list)
{
	// Use fopen to open the file for read
	// Return NULL address if fopen fails
	FILE * file = fopen(filename, "wb");
	if(file == NULL)
	{
		return 0;
	}

	// WRITE LIST INTO FILE
	int count = 1;
	Node *head = list;
	while(head != NULL)
	{
		fwrite(head, sizeof(long), 1, file);
		head = head->next;
		count++;
	}
	
	fclose(file);
	
	return count;
}
//#####################################################################
//Returns Value of Node at a given Index
long getNthNodeValue(Node *head, int index)
{
	Node* curr = head;
	int i = 0;
	while(curr != NULL)
	{
		if (i == index)
		{
			return (curr->value);
		}
		i++;
		curr = curr->next;
	}
}

//Returns Address of Node at a given Index
Node *getNthNodeAddress(Node *head, int index)
{
	Node* curr = head;
	int count = 0;
	while(curr != NULL)
	{
		if (count == index)
		{
			return curr;
		}
		count++;
		curr = curr->next;
	}
}

//get size of Linked list
int getCount(Node* head)
{
	int count = 0;
	Node* curr = head;
	while(curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

//free Linked list
void deleteList(Node **head)
{
	Node *curr = *head;
	Node *next = NULL;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*head = NULL;
}

// add node to Linked list
void addNode(Node **head, long val)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->value = val;
	newNode->next = NULL;

	if(*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		Node *lastNode = *head;
		while(lastNode->next != NULL)
		{
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
	}
}

//INSERTION SORT ALGORITHM
Node* insert(Node* head, Node* index, Node* val){
   if(head == index) 
   {
       val->next = head;
       return val;
   }
   Node* temp = head;
   while(temp->next != index) 
   {
       temp = temp->next;
   }
   
   val->next = temp->next;
   temp->next = val;
   
   return head;
}   
Node* insertion_sort(Node* head)
{

   Node* sorted = head;
   Node* prev = head; 
   Node* node1;
   Node* node2;
   
   while(prev->next != NULL) 
   {    
       node1 = sorted;
	   
	   while(prev->next != NULL && node1 != prev->next && node1->value < prev->next->value)
	   {
        node1 = node1->next;
	   }
       if(prev->next != node1) 
	   { 
           node2 = prev->next;
           prev->next = prev->next->next;
           sorted = insert(sorted,node1,node2);
            
       }
	   else
	   { 
        prev = prev->next;
       }
   }
   return sorted;
}
//get number of sublists
int getNumSublists(int k, int size)
{
	if((size % k) == 0)
	{
		return k;
	}
	else
	{
	return (size % k);
	}
}
/* //printlist
void printList(Node *head)
{
    Node *temp = head;

    //iterate the entire linked list and print the data
    while(temp != NULL)
    {
         printf("%d->", temp->value);
         temp = temp->next;
    }
    printf("NULL\n");
}*/
//#####################################################################

//SHELLSORT ALGORITHM
Node *List_Shellsort(Node *list, long *n_comp)
{
	// 1. Acquire Size and K Value
	int size = getCount(list);
  	int k = 1;
	while(k <= size)
  	{
    	k = (3 * k) + 1;
  	}
 	k = (k - 1)/3;
    
	Node *OGhEAD = list;      // copy of list head
	Node *realHead = list;    // copy of list head
	Node *replaceHead = list; // copy of list head
	Node *finalHEAD = NULL; 
	
	//2. sort the linked list for every k > 0
	while(k > 1)
	{
		OGhEAD = realHead;
		replaceHead = realHead;
		// 3a. Determine how many sublists are needed
		int num_sublists = getNumSublists(k,size);
        
		// 3b. Create each sublist to be sorted
		int x;
		for(x = 1; x <= num_sublists; x++)
        {
			//4. allocate memory for sublist Nodes
			Node *listHead = NULL;
			//5. store every k gap value into sublist
			int i;
			for(i = 0; i < size; i+=k)
			{
				long val = getNthNodeValue(OGhEAD, i);
				addNode(&listHead, val);
			}
			//6. sort the sublist using insertionSort
			listHead = insertion_sort(listHead);
			//7. put back sorted sublist
			int j;
			Node *Start = listHead;
			for(j = 0; j < size; j+=k)
			{
				Node* replace = getNthNodeAddress(replaceHead, j);	
      			(*n_comp)++; 			// Number of Comparisons
				replace->value = Start->value;
				Start = Start->next;
			}
			deleteList(&listHead);
			replaceHead = replaceHead->next;
			OGhEAD = OGhEAD->next;	
		}
    	k = (k - 1)/3;
	}

	finalHEAD = insertion_sort(realHead); //final insertion sort k = 1
	return finalHEAD;
}






