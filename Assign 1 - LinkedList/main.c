/********************************************************************************************************************
PROGRAM: Assignment1 - CST8234_013
AUTHOR: Kevin Lai, Xing Yi Wu, Greenish Kumar
DATE: Mar 16, 2018
PURPOSE: to use linked list to store rental properties in a node's payload. Things that we learned in this
		 assignment is that if you pass in a reference to the linked list's head than you can manipulate the
		 linked list(removing and inserting nodes).
LEVEL OF DIFFICULTY: 4/5
CHALLENGES: Removing a node from the linked list, handling exceptions in the menu so program does not crap out
HOURS SPENT: 60+
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"
#include "rental.h"
#include "sort.h"
void menu(char *choice, node **currentList);
void commandHelp();
void commandAll(node **currentList, int index, int nextProperty);

/*main to start program and invoke menu*/
int main()
{
	srand(time(NULL));

	char choice[8];
	node *currentList[] = { NULL, NULL };  /*array of pointers to nodes (default, favorites)*/

	menu(choice, currentList);

	return 0;
}

/*print the valid commands that can be used (HELP Command)*/
void commandHelp()
{
	printf("\nValid commands are:\n");
	printf("\th  - display this help\n");
	printf("\ta  - display all the rental properties on the current list\n");
	printf("\tf  - switch to the favorites list\n");
	printf("\td  - switch to the default list\n");
	printf("\tl  - 'swipe left' on the current rental property\n");
	printf("\tr  - 'swipe right' on the current rental property\n");
	printf("\tn  - skip to the next rental property\n");
	printf("\tsa - set the sorting to 'by address'\n");
	printf("\tsn - set the sorting to 'by number of rooms'\n");
	printf("\tsr - set the sorting to 'by rent'\n");
	printf("\tsd - set the sorting to 'by distance'\n");
	printf("\tq  - quit the program\n\n");
}

/*print summary and a specific property to see if user is interested*/
void commandAll(node **currentList, int index, int nextProperty)
{
	printSummary(currentList[index], index);
	if (currentList[index] != NULL)
	{
		printNode(getNodeAtIndex(currentList[index], nextProperty));
	}
	else
	{
		printf("\n\nNo more rental properties\n\n");
	}
}

/*handle all the user inputs and prints the corresponding output to the screen*/
void menu(char *choice, node **currentList)
{
	int index = 0; /* used to change between defaults and favorites */
	int nextProperty = 0; /*shift to next property in the list*/
	int(*pComparator)(property *a, property *b) = NULL; /*function pointer used to switch between comparators*/

	/*when program executes create 6 properties in the default linked list*/
	for (int i = 0; i < 6; i++)
	{
		node *newNode = createNode();
		appendNode(&currentList[index], newNode);
	}
	printSummary(currentList[index], index);
	printNode(getNodeAtIndex(currentList[index], nextProperty));

	do
	{
		printf("\nCommand ('h' for help): ");
		scanf("%7s", choice);

		if (strcmp(choice, "h") == 0)  /*call help to see all valid commands*/
		{
			commandHelp();
		}
		else if (strcmp(choice, "a") == 0)  /*display all properties of current Linked List*/
		{
			commandAll(currentList, index, nextProperty);
		}
		else if (strcmp(choice, "f") == 0)  /*switch to favorite list and display all properties*/
		{
			index = 1;
			nextProperty = 0;
			commandAll(currentList, index, nextProperty);
		}
		else if (strcmp(choice, "d") == 0)  /*switch to default list and 50% of generating a new property and display all properties*/
		{
			index = 0;
			nextProperty = 0;

			if (rand() % 2 == 0)
			{
				node *newNode = createNode();
				appendNode(&currentList[index], newNode);
			}
			commandAll(currentList, index, nextProperty);
		}
		else if (strcmp(choice, "l") == 0)  /*swipe left and remove rental listing from current Linked List*/
		{
			if (currentList[index] != NULL)
			{
				removeNodeAtIndex(&currentList[index], nextProperty);
				printf("\n\nRental property deleted\n\n");

				if (getNodeAtIndex(currentList[index], nextProperty) == NULL)
				{
					nextProperty = 0;
				}

				if (currentList[index] == NULL)
				{
					printf("\nNo more rental properties\n\n");
				}
			}
			else
			{
				printf("\n\nNo more rental properties\n\n");
			}
		}
		else if (strcmp(choice, "r") == 0)  /*move property over to favorites*/
		{
			if (index == 0 && currentList[index] != NULL)
			{
				appendNode(&currentList[index + 1], removeNodeAtIndex(&currentList[index], nextProperty));
				printf("\n\nRental property moved to your favorites list\n\n");
				if (getNodeAtIndex(currentList[index], nextProperty) == NULL)
				{
					nextProperty = 0;
				}

				if (currentList[index] == NULL)
				{
					printf("\nNo more rental properties\n\n");
				}
			}
			else if (currentList[index] == NULL)
			{
				printf("\n\nThere are no properties to move to favorites\n\n");
			}
			else
			{
				printf("\n\nThis rental property is already on your favorites list\n");
			}
		}
		else if (strcmp(choice, "n") == 0)  /*skip to the next property on the list*/
		{
			if (getCount(currentList[index]) - 1 > nextProperty)
			{
				printf("\n");
				nextProperty++;
			}
			else if (currentList[index] == NULL)
			{
				printf("\n\nThere are no rental properties ..\n\n");
			}
			else
			{
				printf("\n\nThis is the last property\n\n");
			}
		}
		else if (choice[0] == 's')  /*if first letter of user input is 's' than check 2nd letter to assign function pointer to proper sort*/
		{
			if (choice[1] == 'a')
			{
				pComparator = &differenceAddress;
			}
			else if (choice[1] == 'n')
			{
				pComparator = &differenceRoom;
			}
			else if (choice[1] == 'r')
			{
				pComparator = &differenceRent;
			}
			else if (choice[1] == 'd')
			{
				pComparator = &differenceDistance;
			}
			else
			{
				printf("That is not a supported command\n");
				commandHelp();
			}

			if (choice[1] == 'a' || choice[1] == 'n' || choice[1] == 'r' || choice[1] == 'd')
			{
				if (currentList[index] != NULL)
					sort(currentList[index], pComparator);
				commandAll(currentList, index, nextProperty);
			}
		}
		else if (strcmp(choice, "q") == 0)  /*free up both linked list(favorite and default) then quit*/
		{
			freeList(&currentList[0]);
			freeList(&currentList[1]);
			printf("Goodbye!\n");
		}
		else
		{
			printf("That is not a supported command\n");
			commandHelp();
		}

		if (currentList[index] != NULL && (strcmp(choice, "l") == 0 || strcmp(choice, "r") == 0 || strcmp(choice, "n") == 0))
		{
			if (currentList[index] != NULL)
				printNode(getNodeAtIndex(currentList[index], nextProperty));
		}

	} while (strcmp(choice, "q") != 0);  /*end do while loop if user inputs q (quit)*/
}



