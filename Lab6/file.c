/********************************************************************************************************************
PROGRAM: Lab6 - CST8234_013
AUTHOR: Kevin Lai
DATE: April 02, 2018
PURPOSE: Read from a file and assign data to properties, display errors using stderr if bad data is read.
		 Write data back out to properties.out in a certain format. Lab helped learn about using file pointers
		 to read and write file.
LEVEL OF DIFFICULTY: 4/5
CHALLENGES: Read in data from file (found out that fgets is good for reading line by line)
HOURS SPENT: 8
*********************************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "rental.h"
#include "sort.h"

#define MAX_LINE_LENGTH 512
#define STREETNAMESIZE 11
#define STREETNUMBERSIZE 13
#define RENTSIZE 5
#define ROOMSIZE 6

bool readProperties(char *strFilename, RentalProperty **ppProperties)
{
	// YOU NOW NEED TO IMPLEMENT CODE TO OPEN THE SPECIFIED FILE, AND READ IN THE LIST, AS PER THE LAB REQUIREMENTS
	FILE* inFile = fopen(strFilename, "r");   /*create file pointer and open for read*/
	char strLine[MAX_LINE_LENGTH];
	char strRemainder[MAX_LINE_LENGTH];  /*hold the remaining content to copy over*/
	char strArguments[MAX_LINE_LENGTH];  /*hold the arguments*/
	int rc = 0;
	int numProperty = countProperties(*ppProperties);

	if (inFile != NULL)
	{

		while (fgets(strLine, MAX_LINE_LENGTH, inFile))
		{
			rc = 0;

			/*allocate a new property and set streetName to null and -1 as default for streetNumber, rent, rooms*/
			*ppProperties = realloc(*ppProperties, sizeof(RentalProperty) * (numProperty + 1));
			(*ppProperties + numProperty)->streetName = NULL;
			(*ppProperties + numProperty)->streetNumber = -1;
			(*ppProperties + numProperty)->rent = -1;
			(*ppProperties + numProperty)->rooms = -1;

			do
			{
				rc = sscanf(strLine, "%[^,], %[^\n]", strArguments, strRemainder);

				if (strncmp(strArguments, "streetName=", STREETNAMESIZE) == 0)
				{
					if (strlen(strArguments) > STREETNAMESIZE)
					{
						(*ppProperties + numProperty)->streetName = calloc(1, sizeof(strArguments));
						sscanf(strArguments + STREETNAMESIZE, "%[^\n]", (*ppProperties + numProperty)->streetName);
					}
				}
				else if (strncmp(strArguments, "streetNumber=", STREETNUMBERSIZE) == 0)
				{
					if (strlen(strArguments) > STREETNUMBERSIZE)
						sscanf(strArguments + STREETNUMBERSIZE, "%d", &(*ppProperties + numProperty)->streetNumber);
				}
				else if (strncmp(strArguments, "rent=", RENTSIZE) == 0)
				{
					if (strlen(strArguments) > RENTSIZE)
						sscanf(strArguments + RENTSIZE, "%d", &(*ppProperties + numProperty)->rent);
				}
				else if (strncmp(strArguments, "rooms=", ROOMSIZE) == 0)
				{
					if (strlen(strArguments) > ROOMSIZE)
						sscanf(strArguments + ROOMSIZE, "%d", &(*ppProperties + numProperty)->rooms);
				}
				else
				{
					fprintf(stderr, "Invalid input at line %d on %s\n", (numProperty + 1), strArguments);
				}

				sscanf(strRemainder, "%[^\n]", strLine);  /*copy contents of strRemainder into strLine*/

			} while (rc > 1);

			/*check to see if any property members are null and if so spit out a error message and quit*/
			if ((*ppProperties + numProperty)->streetName == NULL)
			{
				fprintf(stderr, "Line%d is missing a streetName... cannot create property\n", numProperty + 1);
				return false;
			}
			else if ((*ppProperties + numProperty)->streetNumber == -1)
			{
				fprintf(stderr, "Line%d is missing a streetNumber... cannot create property\n", numProperty + 1);
				return false;
			}
			else if ((*ppProperties + numProperty)->rent == -1)
			{
				fprintf(stderr, "Line%d is missing a rent... cannot create property\n", numProperty + 1);
				return false;
			}
			else if ((*ppProperties + numProperty)->rooms == -1)
			{
				fprintf(stderr, "Line%d is missing a room... cannot create property\n", numProperty + 1);
				return false;
			}
			else
			{
				numProperty++;
			}
		}

		/*create null terminator property and set rent to -1*/
		*ppProperties = realloc(*ppProperties, sizeof(RentalProperty) * (numProperty + 1));
		(*ppProperties + numProperty)->rent = -1;

		fclose(inFile);  /*close file*/
		return true;		// everything was successfull
	}
	else
	{
		fprintf(stderr, "The file %s could not be read \n", strFilename);
		return false;
	}
}

/* function that writes out to file properties.out*/
bool writeProperties(char *strFilename, RentalProperty *pProperties, SORT_METHOD eSortMethod, bool isReverse, int nNumResults, int nMin, int nMax, bool isAppend)
{
	sort(pProperties, eSortMethod);
	printList(pProperties, eSortMethod, isReverse, nNumResults, nMin, nMax);

	// YOU NOW NEED TO IMPLEMENT CODE TO OPEN THE SPECIFIED FILE, AND WRITE OUT THE LIST, AS PER THE LAB REQUIREMENTS

	FILE *outFile = isAppend ? fopen(strFilename, "a") : fopen(strFilename, "w");  /*ternary condition to decide between append or write to a file */
	int numProperty = countProperties(pProperties);
	int i = 0;  /*variable used to loop through properties*/

	if (outFile != NULL)
	{
		while (i < numProperty)
		{
			fprintf(outFile, "streetName=%s,", (pProperties + i)->streetName);
			fprintf(outFile, "streetNumber=%d,", (pProperties + i)->streetNumber);
			fprintf(outFile, "rent=%d,", (pProperties + i)->rent);
			fprintf(outFile, "rooms=%d\n", (pProperties + i)->rooms);
			i++;
		}

		/*free up the streetNames that were calloc'd for all the properties*/
		for (i = 0; i < numProperty; i++)
		{
			free((pProperties + i)->streetName);
		}

		/*free the properties*/
		free(pProperties);
		fclose(outFile);

		return true;		// everything was successfull
	}
	else
	{
		fprintf(stderr, "The file %s could not be written \n", strFilename);
		return false;
	}
}
