/********************************************************************************************************************
PROGRAM: Assignment1 - CST8234_013
AUTHOR: Kevin Lai, Xing Yi Wu, Greenish Kumar
DATE: Mar 16, 2018
PURPOSE: Header file to hold all struct and function declarations for node.c
*********************************************************************************************************************/

typedef struct
{
	int streetNum;
	char *streetName;
	int numOfRooms;
	int rent;
	int distance;
}property;

typedef struct node
{
	property *pProperty;
	struct node *next;
}node;

node* createNode();
void appendNode(node **ppHead, node *pNewNode);
void insertNode(node **ppHead, node *pNewNode, int i);
node *removeNodeAtIndex(node **ppHead, int i);
node *getNodeAtIndex(node *pHead, int i);
int getCount(node *pHead);
void freeList(node **pHead);

