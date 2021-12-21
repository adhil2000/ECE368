#include "hbt.h"

Tnode* AVL_Load_From_File(char *filename, Tnode* head);
void AVL_Save_To_File(FILE* file, Tnode* node);
int getMax(int x, int y);
int getHeight(Tnode* node);
int getBalance(Tnode* node);
int getNewHeight(Tnode* node);
void freeTree(Tnode* node);
Tnode* newNode(int key);
Tnode* clockRight(Tnode* node);
Tnode* clockLeft(Tnode* node);
Tnode* balanceTree(Tnode* node, int key);
Tnode* insertNode(Tnode* node, int key);
Tnode* deleteNode(Tnode* node, int key);
int isValidTree(Tnode* node);
int isHeightBalanced(Tnode* node);
Tnode* createBST(int* keys, char* nodes, int* i, int size);
