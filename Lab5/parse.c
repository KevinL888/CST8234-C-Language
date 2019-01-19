/********************************************************************************************************************
PROGRAM: Lab5 - CST8234_013
AUTHOR: Kevin Lai
DATE: Mar 26, 2018
PURPOSE: Parse Arguments that the user has entered at the command line. Assign to corresponding variables
		 e.g.(peSortMethod, pnNumResults, pnMin, pnMax). Handle invalid arguments and EXIT_FAILURE
		 or EXIT_SUCCESS if all arguments are valid flags with proper input.
LEVEL OF DIFFICULTY: 3/5
CHALLENGES: Handling Both GNU and POSIX Options
HOURS SPENT: 8
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "types.h"
#include "rental.h"
#include "sort.h"
#define	MINMAXSIZE 6
#define	SORTSIZE 7
#define	REVERSESIZE 9
#define	LISTSIZE 10

void parseArgs(char *strPattern, char* argv[], int iArg, int *pnNum, bool *isPosix, char *validArgs[]);
int checkUserInput(char *strCommand, char *argv);
void checkSortInput(char *strCommand, SORT_METHOD *peSortMethod, char *argv);
bool parseArguments(int argc, char *argv[], bool *pbReverse, SORT_METHOD *peSortMethod, int *pnNumResults, int *pnMin, int *pnMax);

/************************************************
 * Note, this function always exits the program!
 ************************************************/
void printHelpAndExit(char *strCommand, int exitCode)
{
	if (exitCode == EXIT_SUCCESS)
		printf("\n%s - print some rental properties with user-selectable formatting options.\n", strCommand);

	printf("\nUsage: %s [arguments]\n\n", strCommand);
	printf("Arguments:\n\n");
	printf("    -r, --reverse\t\tPrint the results in reverse order\n");
	printf("    -m <NUM>, --min=<NUM>\tOnly show values that are greater than or equal to the NUM\n");
	printf("    -M <NUM>, --max=<NUM>\tOnly show values that are less than or equal to the NUM\n");
	printf("    -l <NUM>, --listing=<NUM>\tShows max <NUM> of property listings\n");
	printf("    -s <SORT>, --sort=<SORT>\tMandatory: Use one of the following SORT methods:\n");
	printf("\t\t\t\t\tbyRent - sort by the rent\n");
	printf("\t\t\t\t\tbyRooms - sort by the number of room\n");
	printf("\t\t\t\t\tbyAddress - sort by address\n");
	printf("    -h, --help\t\t\tPrint this message\n\n");

	exit(exitCode);
}

void parseArgs(char *strPattern, char* argv[], int iArg, int *pnNum, bool *isPosix, char *validArgs[])
{
	int i; /*to loop through all the valid args*/
	bool isFlag = false;  /*boolean to see if the next Arg is a flag*/

	if (strncmp(argv[iArg], strPattern, strlen(strPattern)) == 0)
		*isPosix = false;

	if (!*isPosix && strlen(argv[iArg]) > strlen(strPattern))
	{
		*pnNum = checkUserInput(argv[iArg] + strlen(strPattern), argv[iArg]);
	}
	else if (*isPosix && argv[iArg + 1] != NULL)
	{
		/*loop through to see if following Arg after POSIX tag is a flag. If true than no Arg was given*/
		for (i = 0; i < 12; i++)
		{
			if (strncmp(validArgs[i], argv[iArg + 1], strlen(validArgs[i])) == 0)
			{
				isFlag = true;
				break;
			}
		}
		/*parse Arg since next Arg was not a flag*/
		if (!isFlag)
			*pnNum = checkUserInput(argv[iArg + 1], argv[iArg]);
		else
		{
			/* set to false because no argument was given after POSIX tag (so doesn't increment iArg counter */
			*isPosix = false;
			if (strcmp(argv[iArg], "-M") == 0)
				*pnNum = INT_MAX;
		}
	}
	else
	{
		*isPosix = false;
		/*no argument was given so set default size*/
		if (strcmp(strPattern, "--max=") == 0 || strcmp(argv[iArg], "-M") == 0)
			*pnNum = INT_MAX;
	}
	/*check to see if number that was parsed is a negative number and exit on failure if true*/
	if (*pnNum < 0)
	{
		printf("Cannot specify negative number");
		printHelpAndExit(argv[iArg], EXIT_FAILURE);
	}
}

/* assigns sort method to corresponding input*/
void checkSortInput(char *strCommand, SORT_METHOD *peSortMethod, char *argv)
{
	if (strcmp(strCommand, "byRent") == 0)
		*peSortMethod = sortByRent;
	else if (strcmp(strCommand, "byRooms") == 0)
		*peSortMethod = sortByRooms;
	else if (strcmp(strCommand, "byAddress") == 0)
		*peSortMethod = sortByAddress;
	else
	{
		printf("%s - Must provide a proper sorting method", argv);
		printHelpAndExit(argv, EXIT_FAILURE);
	}
}

/*validate user input for (min/max and max property listings) returns an integer if valid*/
int checkUserInput(char *strCommand, char *argv)
{
	char junk;
	int value = -1;
	int rc = sscanf(strCommand, "%d%c", &value, &junk);
	if (rc != 1)
	{
		printf("illegal argument '%s' in %s\n", strCommand, argv);
		printHelpAndExit(argv, EXIT_FAILURE);
	}
	return value;
}

/* function that takes in all arguments from main*/
bool parseArguments(int argc, char *argv[], bool *pbReverse, SORT_METHOD *peSortMethod, int *pnNumResults, int *pnMin, int *pnMax)
{
	bool isPosix = true;  /* Check to see if POSIX OR GNU*/
	char *strPattern;  /*String literal to hold GNU flags */
	int iArg;  /*Variable used to loop through command arguments*/
	char * validArgs[] = { "-r","--reverse", "-m", "--min=", "-M", "--max=", "-l", "--listing=", "-s", "--sort=", "-h", "--help" };

	// does the program name start with a local path specifier?
	char	*strCommand = argv[0];
	if (strncmp("./", strCommand, 2) == 0)
		strCommand += 2;

	/*check to see if any arguments were given */
	if (argc == 1)
	{
		printf("\n%s: you must provide some arguments.\n", strCommand);
		printHelpAndExit(strCommand, EXIT_FAILURE);
	}
	else
	{
		for (iArg = 1; iArg < argc; iArg++)
		{
			isPosix = true;
			if (strcmp(argv[iArg], "-h") == 0 || strcmp(argv[iArg], "--help") == 0)  /*help flag for printing all valid options*/
			{
				printHelpAndExit(argv[iArg], EXIT_SUCCESS);
			}
			else if (strcmp(argv[iArg], "-s") == 0 || strncmp(argv[iArg], "--sort=", SORTSIZE) == 0)  /*parse sort flag*/
			{
				strPattern = "--sort=";
				if (strncmp(argv[iArg], strPattern, SORTSIZE) == 0)
					isPosix = false;

				if (!isPosix && strlen(argv[iArg]) > SORTSIZE)
				{
					checkSortInput(argv[iArg] + strlen(strPattern), peSortMethod, argv[iArg]);
				}
				else if (isPosix && argv[iArg + 1] != NULL && argv[iArg + 1][0] != '-')
				{
					checkSortInput(argv[iArg + 1], peSortMethod, argv[iArg]);
				}
				else
				{
					printf("Must provide a sorting method");
					printHelpAndExit(argv[iArg], EXIT_FAILURE);
				}

				if (isPosix)
					iArg++;
			}
			else if (strcmp(argv[iArg], "-m") == 0 || strncmp(argv[iArg], "--min=", MINMAXSIZE) == 0)  /*set the minimum value for print*/
			{
				strPattern = "--min=";
				parseArgs(strPattern, argv, iArg, pnMin, &isPosix, validArgs);

				if (isPosix)
					iArg++;
			}
			else if (strcmp(argv[iArg], "-M") == 0 || strncmp(argv[iArg], "--max=", MINMAXSIZE) == 0)  /*set the maximum value for print*/
			{
				strPattern = "--max=";
				parseArgs(strPattern, argv, iArg, pnMax, &isPosix, validArgs);

				if (isPosix)
					iArg++;
			}
			else if (strcmp(argv[iArg], "-l") == 0 || strncmp(argv[iArg], "--listing=", LISTSIZE) == 0)  /*set maximum number of rental properties to list*/
			{
				strPattern = "--listing=";
				parseArgs(strPattern, argv, iArg, pnNumResults, &isPosix, validArgs);

				if (isPosix)
					iArg++;
			}
			else
			{
				if (strcmp(argv[iArg], "-r") != 0 && strncmp(argv[iArg], "--reverse", REVERSESIZE) != 0)
				{
					printf("Unrecognized Flag %s\n", argv[iArg]);
					printHelpAndExit(argv[iArg], EXIT_FAILURE);
				}
			}
		} /*end for loop (finished parsing all command arguments)*/


		  /*check to see if sort flag has been used*/
		if (*peSortMethod == sortByRooms)
			*pbReverse = true;
		else if (*peSortMethod == sortByRent || *peSortMethod == sortByAddress)
			*pbReverse = false;
		else
		{
			printf("No sorting method specified");
			printHelpAndExit(argv[--iArg], EXIT_FAILURE);
		}

		/*check to see if user has used the min/max argument with sortByAddress*/
		for (iArg = 1; iArg < argc; iArg++)
		{
			if (strcmp(argv[iArg], "-m") == 0 || strcmp(argv[iArg], "-M") == 0 || strncmp(argv[iArg], "--min=", MINMAXSIZE) == 0 || strncmp(argv[iArg], "--max=", MINMAXSIZE) == 0)
			{
				if (*peSortMethod == sortByAddress)
				{
					printf("Cannot specify a min/max value with sortByAddress");
					printHelpAndExit(argv[iArg], EXIT_FAILURE);
				}
			}

			/*check to see if reverse flag has been used*/
			if (strcmp(argv[iArg], "-r") == 0 || strncmp(argv[iArg], "--reverse", REVERSESIZE) == 0)
			{
				if (*peSortMethod == sortByRooms)
					*pbReverse = false;
				else
					*pbReverse = true;
			}
		}
		EXIT_SUCCESS;
	}
	return true;
}

