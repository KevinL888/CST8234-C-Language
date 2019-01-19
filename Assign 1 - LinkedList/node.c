/********************************************************************************************************************
PROGRAM: Assignment1 - CST8234_013
AUTHOR: Kevin Lai, Xing Yi Wu, Greenish Kumar
DATE: Mar 16, 2018
PURPOSE: to handle manipulation of linked list eg.(creating node, appending node to end of list, removing node,
		 inserting node at a specific index, counting total nodes in linked list, searching for a node).
*********************************************************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include "node.h"
#include "rental.h"

/*create a new node and call createProperty to assign struct members*/
node* createNode()
{
	node *pNewNode = calloc(1, sizeof(node));
	pNewNode->pProperty = createProperty();
	return pNewNode;
}

/*append new node to the linked list, if head is null than assign new node to head
otherwise append to end of the list and set next to point to null*/
void appendNode(node** ppHead, node* pNewNode)
{
	if (*ppHead == NULL)
	{
		*ppHead = pNewNode;
	}
	else
	{
		node *temp = *ppHead;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = pNewNode;
	}
	pNewNode->next = NULL;
}

/*insert a node at a specific index given in the parameter*/
void insertNode(node **ppHead, node *pNewNode, int i)
{
	if (*ppHead == NULL)
	{
		*ppHead = pNewNode;
	}
	else if (i == 0)
	{
		pNewNode->next = *ppHead;
		*ppHead = pNewNode;
	}
	else
	{
		int counter = 0;

		node *temp = *ppHead;

		while (temp->next != NULL)
		{
			if (counter == i - 1)
			{
				break;
			}
			temp = temp->next;
			counter++;
		}
		pNewNode->next = temp->next;
		temp->next = pNewNode;
	}
}

/*using a index passed in the parameter to traverse through the linked list
and return the reference of that removed node*/
node *removeNodeAtIndex(node **ppHead, int i)
{
	int counter = 0;

	node **temp = ppHead;

	if (*temp == NULL)
	{
		return *ppHead;
	}
	else
	{
		while (counter != i)
		{
			temp = &(*temp)->next;
			counter++;
		}

		node *removeNode = *temp;
		*temp = removeNode->next;
		removeNode->next = NULL;

		return removeNode;
	}
}

/*using a index passed in the parameter to traverse through the linked list and return reference to a node */
node *getNodeAtIndex(node *pHead, int i)
{
	int counter = 0;

	while (pHead != NULL)
	{
		if (counter == i)
		{
			break;
		}
		pHead = pHead->next;
		counter++;
	}
	return pHead;
}

/*traverse through linked list and use a counter to return the total amount of nodes*/
int getCount(node *pHead)
{
	int counter = 0;

	while (pHead != NULL)
	{
		pHead = pHead->next;
		counter++;
	}
	return counter;
}

/*free up the linked list*/
void freeList(node **pHead)
{
	node *temp = *pHead;

	while (*pHead != NULL)
	{
		temp = *pHead;
		*pHead = (*pHead)->next;
		free(temp->pProperty);
		free(temp);
	}
}
