/********************************************************************************************************************
PROGRAM: Assignment2 - CST8234_013
AUTHOR: Kevin Lai, Seongyeop Jeong
DATE: Apr 18, 2018
PURPOSE: User interface for Guessing game and handles all prints to the console (Parent process)
*********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void mySigHandler(int signum);
int processGuess(int compare, int guess);

void runAsParent(int fdRead, int fdWrite)
{
	/*Register signal handlers*/
	if (signal(SIGUSR1, mySigHandler) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGUSR1.\n");

	if (signal(SIGUSR2, mySigHandler) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGUSR2.\n");

	if (signal(SIGCONT, mySigHandler) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGCONT.\n");

	int rc = 0;  /*number of successful writes to scanf*/
	int guess;  /*holds the users guess*/
	int compareGuess; /*used to hold return values from child -1, 0, 1, 2*/

	while (1)
	{
		printf("Enter a number between 0-99 (you have 10 seconds to make a guess): ");

		do
		{
			rc = scanf("%d", &guess);

			if (rc == 0)
			{
				while (getchar() != '\n');
				rc = 1;
				guess = -1;
			}

		} while (rc < 1);

		write(fdWrite, &guess, sizeof(guess));  /*Write guess through pipe to child process*/
		pause();  /*Pause and wait for signal to let us know when there is data in our pipe*/
		read(fdRead, &compareGuess, sizeof(compareGuess));

		if (processGuess(compareGuess, guess))
			break;
	}
}

/*Signal handler function that handles all of our signals in a switch statements (SIGUSR1, SIGUSR2, SIGCONT)*/
void mySigHandler(int signum)
{
	switch (signum)
	{
		case SIGUSR2:	fprintf(stderr, "\nAre you still there? Time is running out!\n");
			if (signal(SIGUSR2, mySigHandler) == SIG_ERR)
				fprintf(stderr, "Can't catch SIGUSR2.\n");
			break;
		case SIGUSR1:	printf("Sorry, you ran out of time!\n\n");
			exit(EXIT_SUCCESS);
			break;
		case SIGCONT:	if (signal(SIGCONT, mySigHandler) == SIG_ERR)
			fprintf(stderr, "Can't catch SIGCONT.\n");
			break;
		default:
			break;
	}
}

/*Process Guess and let user know if the number is invalid, greater, less or equal (-1 for less, 0 for equal and 1 for greater and 2 for invalid)*/
int processGuess(int compare, int guess)
{
	if (compare == 2)
	{
		fprintf(stderr, "Invalid input...\n\n");
		return 0;
	}
	else if (compare == 0)
	{
		fprintf(stdout, "Congratulations, you guessed the number (%d) correctly!\n\n", guess);
		return 1;
	}
	else if (compare == -1)
	{
		fprintf(stdout, "Your guess was too low\n\n");
		return 0;
	}
	else
	{
		fprintf(stdout, "Your guess was too high\n\n");
		return 0;
	}
}
