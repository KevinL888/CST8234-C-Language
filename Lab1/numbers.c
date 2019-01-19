#include <stdio.h>
#include <stdlib.h>

/* PROGRAM: Lab1 - CST8234_013
AUTHOR: Kevin Lai
DATE: Jan 18, 2018
PURPOSE: Debug a simple program that iterates through 100 integers and finds multiples of the arguments that are passed
LEVEL OF DIFFICULTY: 1
CHALLENGES: debugging the problem and wouldn't let me compile when I had int i as a variable in the for loop
HOURS SPENT: 1 and half
*/

int main(int argc, char *argv[])
{
	if (argc == 4) /* Did we enter the correct number of args? */
	{
		int n1 = atoi(argv[1]);	/* convert 1st command line arg from a string (e.g., "5") to an integer (e.g., 5) */
		int n2 = atoi(argv[2]);	/* convert 2nd command line arg from a string to an integer */
		int n3 = atoi(argv[3]);	/* convert 3rd command line arg from a string to an integer */

		int i;   /* variable used to iterate 1 - 100 */

				 /* iterate over the first 100 integers */
		for (i = 1; i <= 100; i++)
		{
			if (i % n1 == 0 && i % n2 == 0 && i % n3 == 0)
				printf("%3d is divisible by ALL %d AND %d AND %d\n", i, n1, n2, n3);

			else if (i % n1 == 0 && i % n2 == 0)
				printf("%3d is divisible by both %d AND %d\n", i, n1, n2);
			else if (i % n1 == 0 && i % n3 == 0)
				printf("%3d is divisible by both %d AND %d\n", i, n1, n3);
			else if (i % n2 == 0 && i % n3 == 0)
				printf("%3d is divisible by both %d AND %d\n", i, n2, n3);

			else if (i % n1 == 0)
				printf("%3d is divisible by %d\n", i, n1);
			else if (i % n2 == 0)
				printf("%3d is divisible by %d\n", i, n2);
			else if (i % n3 == 0)
				printf("%3d is divisible by %d\n", i, n3);
			else
				printf("%3d\n", i);
		}
	}
	else
		printf("usage: numbers.c [INT] [INT] [INT]\n");

	return EXIT_SUCCESS;
}
