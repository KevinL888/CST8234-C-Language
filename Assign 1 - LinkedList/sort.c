/********************************************************************************************************************
PROGRAM: Assignment1 - CST8234_013
AUTHOR: Kevin Lai, Xing Yi Wu, Greenish Kumar
DATE: Mar 16, 2018
PURPOSE: to handle sort by using comparators e.g.(difference in rooms, rent, address, distance) swap function
		 is used to swap the node's payload.
*********************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"
#include "sort.h"
#include "rental.h"

/*comparator function for number of rooms (if numbers of rooms are the same than compare rent cost)*/
int differenceRoom(property *pStreetA, property *pStreetB)
{
	int diff = pStreetB->numOfRooms - pStreetA->numOfRooms;
	if (diff == 0)
		diff = pStreetB->rent - pStreetA->rent;
	return diff;
}

/*comparator function for rent (if rent cost is the same than compare number of rooms)*/
int differenceRent(property *pStreetA, property *pStreetB)
{
	int diff = pStreetA->rent - pStreetB->rent;
	if (diff == 0)
		diff = pStreetA->numOfRooms - pStreetB->numOfRooms;
	return diff;
}

/*comparator function for address (if address are the same than compare the streetNum*/
int differenceAddress(property *pStreetA, property *pStreetB)
{
	int diff = strcmp(pStreetA->streetName, pStreetB->streetName);
	if (diff == 0)
		diff = pStreetA->streetNum - pStreetB->streetNum;
	return diff;
}

/*comparator function for distance (if distance are the same than compare the rent*/
int differenceDistance(property *pStreetA, property *pStreetB)
{
	int diff = calcDistanceFromCollege(pStreetA) - calcDistanceFromCollege(pStreetB);
	if (diff == 0)
		diff = pStreetA->rent - pStreetB->rent;
	return diff;
}

/*sort rooms using bubble sort (use of boolean to help stop sort if no elements are swapped in a passing)*/
void sort(node *pHead, int(*pComparator)(property *a, property *b))
{
	int i, j;
	bool wasSwapped = true;
	int size = getCount(pHead);
	for (i = 0; i < size - 1 && wasSwapped; i++)
	{
		wasSwapped = false;
		for (j = 0; j < size - i - 1; j++)
		{
			node *a = getNodeAtIndex(pHead, j);
			node *b = getNodeAtIndex(pHead, j + 1);
			if ((*pComparator)(a->pProperty, b->pProperty) > 0)
			{
				swap(a, b);
				wasSwapped = true;
			}
		}
	}
}

/*swap the node's payload (property)*/
void swap(node *pNode_A, node *pNode_B)
{
	property *temp = pNode_A->pProperty;
	pNode_A->pProperty = pNode_B->pProperty;
	pNode_B->pProperty = temp;
}
