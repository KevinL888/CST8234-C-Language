/********************************************************************************************************************
PROGRAM: Assignment1 - CST8234_013
AUTHOR: Kevin Lai, Xing Yi Wu, Greenish Kumar
DATE: Mar 16, 2018
PURPOSE: To handle creation of all properties and print summary in a certain format
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"
#include "rental.h"

/*create a new property and use rand to assign members (streetName, streetNum, numOfRooms, rent, distance)*/
property* createProperty()
{
	char* arrProperty[] = { "Merivale Rd", "Baseline Rd", "Sussex Drive", "Frog Court", "Meadowlands Drive",
							"Greenbriar Ave", "Anderson St", "Hunt Club Rd", "Majestic Drive", "Knoxdale Rd" };

	property *pStreet = calloc(1, sizeof(property));
	pStreet->streetName = arrProperty[(rand() % 10)];
	pStreet->streetNum = (rand() % 200) + 1;
	pStreet->numOfRooms = (rand() % 4) + 1;
	pStreet->rent = 50 * (rand() % (9) + 4);
	pStreet->distance = 100 * (rand() % (36) + 5);
	return pStreet;
}

/*calculate the distance from rental property to college*/
int calcDistanceFromCollege(property *pStreet)
{
	int distance = pStreet->distance + (20 * pStreet->streetNum);
	return distance;
}

/*displays the properties to the screen in a certain format  */
void printSummary(node *pHead, int i)
{
	if (i == 0)
	{
		printf("\n\nUndecided Rental Properties\n");
	}
	else
	{
		printf("\n\nFavorite Rental Properties\n");
	}

	printf("Address\t\t\t\t\t# Rooms\t   Rent/Room\t   Distance\n");
	printf("--------------------------\t\t-------\t   ---------\t  ---------\n");

	while (pHead != NULL)
	{
		printf("%3d %-15s\t\t\t%7d\t%12d%12.2f km\n", pHead->pProperty->streetNum, pHead->pProperty->streetName, pHead->pProperty->numOfRooms, pHead->pProperty->rent, (float) calcDistanceFromCollege(pHead->pProperty) / 1000);
		pHead = pHead->next;
	}
	printf("\n");
}

/*print a specific rental property and ask what they think about the property*/
void printNode(node *pHead)
{
	printf("\nWhat do you think about this rental property?\n");
	printf("\tAddr: %d %s, # Rooms: %d, Rent/Room: $%d, Distance: %.2f km\n\n", pHead->pProperty->streetNum, pHead->pProperty->streetName, pHead->pProperty->numOfRooms, pHead->pProperty->rent, (float) calcDistanceFromCollege(pHead->pProperty) / 1000);
}