/********************************************************************************************************************
PROGRAM: Lab4 - CST8234_013
AUTHOR: Kevin Lai
DATE: Feb 19, 2018
PURPOSE: Create a program to store different properties in a struct array. Sort listings by number of rooms,
		 rent and address using bubble sort and comparator function. print all property listing in a proper
		 format to the screen.
LEVEL OF DIFFICULTY: 3/5
CHALLENGES: Finding out how to implement the sort correctly with bubble sort.
HOURS SPENT: 6
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	int streetNum;
	char *streetName;
	int numOfRooms;
	int rent;
}property;

void simulation(property **parrProperty, int arrSize);
void createProperty(property **arrProperty, int arrSize);
void sortByRooms(property **arrProperty, int arrSize);
void sortByRent(property **arrProperty, int arrSize);
void sortByAddress(property **arrProperty, int arrSize);
int differenceRoom(property **arrProperty, int i);
int differenceRent(property **arrProperty, int i);
int differenceAddress(property **arrProperty, int i);
void printProperty(property **arrProperty, int arrSize);

int main()
{
	srand(time(NULL));

	property arrProperty[] = { { 24,"Sussex Drive",0,0 }, { 1,"Sussex Drive",0,0 }, { 5,"Sussex Drive",0,0 },
							   { 77,"Frog Court",0,0 }, { 33,"Fish Lane",0,0 }, { 18,"Meadowlands Drive",0,0 },
							   { 973,"Greenbriar Ave",0,0 }, { 91,"Anderson St",0,0 }, { 180,"Hunt Club Rd",0,0 },
							   { 38,"Majestic Drive",0,0 }, { 766,"Knoxdale Rd",0,0 }, { 68,"Meadowlands Drive",0,0 } };
	int i;
	int arrSize = sizeof(arrProperty) / sizeof(arrProperty[0]);  /*variable used for size of struct array*/
	property **parrProperty = malloc(sizeof(parrProperty) * arrSize);  /*create double pointer and than allocate a block of memory for an array of 12 pointers */

	for (i = 0; i < arrSize; i++)
	{
		parrProperty[i] = &arrProperty[i];  /*dereferencing double pointer and than assign each pointer to point to each element in the struct array*/
	}

	simulation(parrProperty, arrSize);

	return 0;
}

/*Function to simulate the sort, compare, display*/
void simulation(property **pparrProperty, int arrSize)
{
	createProperty(pparrProperty, arrSize);

	sortByRooms(pparrProperty, arrSize);
	printf("\nSorted by Rooms\n");
	printProperty(pparrProperty, arrSize);

	sortByRent(pparrProperty, arrSize);
	printf("\nSorted by Rent\n");
	printProperty(pparrProperty, arrSize);

	sortByAddress(pparrProperty, arrSize);
	printf("\nSorted by Address\n");
	printProperty(pparrProperty, arrSize);

	free(pparrProperty);  /*deallocate double pointer and give memory back to heap*/
}

/*function to assign numbers of rooms and rent using random generator*/
void createProperty(property **pparrProperty, int arrSize)
{
	int i;

	for (i = 0; i < arrSize; i++)
	{
		pparrProperty[i]->numOfRooms = (rand() % 4) + 1;
		pparrProperty[i]->rent = ((rand() % 5) + 8) * 100;
	}
}

/*comparator function for number of rooms (if numbers of rooms are the same than compare rent cost)*/
int differenceRoom(property **pparrProperty, int i)
{
	int diff = pparrProperty[i]->numOfRooms - pparrProperty[i+1]->numOfRooms;
	if (diff == 0)
		diff = pparrProperty[i]->rent - pparrProperty[i+1]->rent;
	return diff;
}

/*comparator function for rent (if rent cost is the same than compare number of rooms)*/
int differenceRent(property **pparrProperty, int i)
{
	int diff = pparrProperty[i]->rent - pparrProperty[i+1]->rent;
	if (diff == 0)
		diff = pparrProperty[i]->numOfRooms - pparrProperty[i+1]->numOfRooms;
	return diff;
}

/*comparator function for address (if address are the same than compare the streetNum*/
int differenceAddress(property **pparrProperty, int i)
{
	int diff = strcmp(pparrProperty[i]->streetName, pparrProperty[i+1]->streetName);
	if (diff == 0)
		diff = pparrProperty[i]->streetNum - pparrProperty[i+1]->streetNum;
	return diff;
}

/*sort rooms using bubble sort (use of boolean to help stop sort if no elements are swapped in a passing)*/
void sortByRooms(property **pparrProperty, int arrSize)
{
	int i, j;
	bool wasSwapped = true;
	property *temp;

	for (i = 0; i < arrSize - 2 && wasSwapped; i++)
	{
		wasSwapped = false;
		for (j = 0; j < arrSize - i - 1; j++)
		{
			if (differenceRoom(pparrProperty, j) > 0)
			{
				temp = pparrProperty[j];
				pparrProperty[j] = pparrProperty[j + 1];
				pparrProperty[j + 1] = temp;
				wasSwapped = true;
			}
		}
	}
}

/*sort rent using bubble sort (use of boolean to help stop sort if no elements are swapped in a passing)*/
void sortByRent(property **pparrProperty, int arrSize)
{
	int i, j;
	bool wasSwapped = true;
	property *temp;

	for (i = 0; i < arrSize - 2 && wasSwapped; i++)
	{
		wasSwapped = false;
		for (j = 0; j < arrSize - i - 1; j++)
		{
			if (differenceRent(pparrProperty, j) > 0)
			{
				temp = pparrProperty[j];
				pparrProperty[j] = pparrProperty[j + 1];
				pparrProperty[j + 1] = temp;
				wasSwapped = true;
			}
		}
	}
}

/*sort address using bubble sort (use of boolean to help stop sort if no elements are swapped in a passing)*/
void sortByAddress(property **pparrProperty, int arrSize)
{
	int i, j;
	bool wasSwapped = true;
	property *temp;

	for (i = 0; i < arrSize - 2 && wasSwapped; i++)
	{
		wasSwapped = false;
		for (j = 0; j < arrSize - i - 1; j++)
		{
			if (differenceAddress(pparrProperty, j) > 0)
			{
				temp = pparrProperty[j];
				pparrProperty[j] = pparrProperty[j + 1];
				pparrProperty[j + 1] = temp;
				wasSwapped = true;
			}
		}
	}
}

/*displays the properties to the screen , sorted by number of rooms, rent and address */
void printProperty(property **pparrProperty, int arrSize)
{
	int i;
	printf("Address\t\t\t\t\t# Rooms\t      Rent\n");
	printf("--------------------------\t\t-------\t   -------\n");

	for (i = 0; i < arrSize; i++)
	{
		printf("%3d %-15s\t\t\t%7d\t%10d\n", pparrProperty[i]->streetNum, pparrProperty[i]->streetName, pparrProperty[i]->numOfRooms, pparrProperty[i]->rent);
	}
}
