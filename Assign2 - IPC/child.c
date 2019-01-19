/********************************************************************************************************************
PROGRAM: Assignment2 - CST8234_013
AUTHOR: Kevin Lai, Seongyeop Jeong
DATE: Apr 18, 2018
PURPOSE: Brains of the guessing game, handles all operations of the game and sends signals to parents process.
*********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
int readLine(int fdRead, int *guess);
void processInput(int guess, int random, int fdWrite);
int idleTask(int timer);

void runAsChild(int fdRead, int fdWrite)
{
	srand(time(NULL));
	int guess;  /*variable to hold our guess that will be read in through pipe from parent process*/
	int timer = 10;  /*set sanity timers*/
	int random = rand() % 100;  /*generate a random number from 0-99*/
	int flags = fcntl(fdRead, F_GETFL, 0);  /*flag variable to set child process to non-blocking reads*/

	/*set non-blocking reads for child and handle error if it could not be set*/
	if (fcntl(fdRead, F_SETFL, flags | O_NONBLOCK))
		fprintf(stderr, "Could not set non - blocking flag\n");
	else
	{

		while (1)
		{
			if (readLine(fdRead, &guess))
			{
				processInput(guess, random, fdWrite);
				timer = 10;  /*set counter back to 10 if sucessfully got a input from parent process*/
			}
			else if (errno == EAGAIN)
			{
				if (idleTask(timer))
					break;
				timer--;
				sleep(1);
			}
			else
			{
				fprintf(stderr, "Error during read %d\n", errno);
			}
		}
	}
}

/*function to read from pipe and handle errors during reading from pipe*/
int readLine(int fdRead, int *guess)
{
	int status = 0;
	int nBytes = read(fdRead, guess, sizeof(guess));
	return nBytes >= 0;

	if (nBytes < 0)
	{
		if (errno != EAGAIN)
			fprintf(stderr, "Error during read %d\n", errno);
	}
	else
		status = 1;

	return status;
}

/*function is like a comparator, takes the guess that was given from parent process and compares with random number generated
if number is equal return 0, less than return -1 and greater than return 1 otherwise return 2 for invalid inputs*/
void processInput(int guess, int random, int fdWrite)
{
	kill(getppid(), SIGCONT);
	int num = 0;

	if (guess < 0 || guess>99)
	{
		num = 2;
		write(fdWrite, &num, sizeof(num));
	}
	else if (guess == random)
	{
		num = 0;
		write(fdWrite, &num, sizeof(num));
		exit(EXIT_SUCCESS);
	}
	else if (guess < random)
	{
		num = -1;
		write(fdWrite, &num, sizeof(num));
	}
	else
	{
		num = 1;
		write(fdWrite, &num, sizeof(num));
	}
}

/*idleTask function to handle sanity timer, 5 seconds send a kill signal SIGUSR1 to parent process and 0 seconds
send a kill signal to SIGUSR2 to parent process that they lost the game and exit*/
int idleTask(int timer)
{
	if (timer == 5)
	{
		kill(getppid(), SIGUSR2);
		return 0;
	}
	else if (timer == 0)
	{
		kill(getppid(), SIGUSR1);
		return 1;
	}
	return 0;
}


