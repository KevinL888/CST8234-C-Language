/********************************************************************************************************************
PROGRAM: Lab3 - CST8234_013
AUTHOR: Kevin Lai
DATE: Feb 13, 2018
PURPOSE: Create a program to simulate a card game, ask user for input of numOfPlayers and cardPerPlayer.
		 Use of rand to shuffle deck than deal cards to players. We than ask users to see who's hand he wants to see.
		 Lab was helpful on learning pointers and how to pass by reference to manipulate data.
LEVEL OF DIFFICULTY: 3/5
CHALLENGES: Finding out way to print out corresponding players hand.
HOURS SPENT: 24+
**********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getPlayerInput(int *pnPlayers);
void getCardsPerPlayer(int *pnPlayers, int *pnCardsPerPlayer);
void swap(char *cards[], int i, int j);
void shuffle(char *cards[]);
void simulation(char *cards[], int cardNum, int hand, int player);
void printHand(char *cards[], int nCardsPerPLayer, int iPlayer, int nPlayer);

int main()
{
	srand(40812704); /*random generator using our student id code*/
	char *deck[52] = { "2D", "2C", "2H", "2S", "3D", "3C", "3H", "3S",
					   "4D", "4C", "4H", "4S", "5D", "5C", "5H", "5S",
					   "6D", "6C", "6H", "6S", "7D", "7C", "7H", "7S",
					   "8D", "8C", "8H", "8S", "9D", "9C", "9H", "9S",
					   "10D", "10C", "10H", "10S", "JD", "JC", "JH", "JS",
					   "QD", "QC", "QH", "QS", "KD", "KC", "KH", "KS",
					   "AD", "AC", "AH", "AS" };

	int hand = 0, player = 0, cardNum = 0;

	getPlayerInput(&player); /*get user input*/

	getCardsPerPlayer(&player, &cardNum); /*get cards per player input*/

	shuffle(deck); /*shuffle the deck using random and swap*/

	simulation(deck, cardNum, hand, player); /* simulation to see players hands */

	return 0;
}


/*Use scanf to get user input of how many players.
 Exception handling done if user inputs less than 1 or non-numeric values*/
void getPlayerInput(int *pnPlayers)
{
	while (*pnPlayers < 1 || *pnPlayers > 52)
	{
		int num = 0;

		printf("How many players? ");
		num = scanf("%d%*[^\n]", pnPlayers);

		if (num == 0)
		{
			while (getchar() != '\n');
			printf("invalid players please enter a number greater than 0 and less than 52\n");
		}

		else if (*pnPlayers < 1 || *pnPlayers>52)
		{
			printf("invalid players please enter a number greater than 0 and less than 52\n");
		}

	}
}

/*Use scanf to get number of cards per players.
Exception handling done if user inputs less than 1, non-numeric values
and card restriction boundary example (1 player/1-52 cards, 4 players, 1-13 cards)*/
void getCardsPerPlayer(int *pnPlayers, int *pnCardsPerPlayer)
{
	int num = 0;
	int cardRestrict = 52 / (*pnPlayers);

	do
	{

		printf("How many cards per player? ");
		num = scanf("%d%*[^\n]", pnCardsPerPlayer);

		if (num == 0)
		{
			while (getchar() != '\n');
			printf("invalid number of cards please enter a positive integer\n");
		}

		else if (*pnCardsPerPlayer > cardRestrict)
		{
			printf("please enter amount of cards between 1-%d\n", cardRestrict);
		}

		else if (*pnCardsPerPlayer < 1)
		{
			printf("invalid number of cards please enter a positive integer\n");
		}

	} while (*pnCardsPerPlayer<1 || *pnCardsPerPlayer>cardRestrict);
}

/*Shuffles deck using random and calls swap function. Deck is passed in by reference*/
void shuffle(char *cards[])
{
	int r = 0;
	int i = 0;
	for (i = 0; i < 52; i++)
	{
		r = rand() % 52;
		swap(cards, i, r);
	}
}

/*Swaps cards by passing random and index in and creating a temp variable to hold a certain index in the array*/
void swap(char *cards[], int i, int r)
{
	char *temp = cards[r];

	cards[r] = cards[i];
	cards[i] = temp;
}


/*Simulate game by asking player who's hand he wants to see than calling printHand function*/
void simulation(char *deck[], int cardNum, int hand, int players)
{
	int num = 0;
	do
	{
		printf("Who's hand do you want to see (or 0 to quit)? ");
		num = scanf("%d%*[^\n]", &hand);

		if (num == 0)
		{
			while (getchar() != '\n');
			hand = players + 1;
		}

		if (hand <= players && hand > 0)
		{
			printHand(deck, cardNum, hand, players);
		}
		else if (hand != 0)
		{
			printf("Invalid hand... ");
		}

	} while (hand != 0);
}

/*prints hand corresponding to which player the user selects, than prints out to the screen*/
void printHand(char *deck[], int nCardsPerPlayer, int iPlayer, int nPlayer)
{
	int i;
	printf("Player %d: [ ", iPlayer);

	for (i = iPlayer - 1; i < nCardsPerPlayer*nPlayer; i += nPlayer)
	{
		printf("%s", deck[i]);
		if (i != nPlayer * nCardsPerPlayer - (nPlayer - (iPlayer - 1)))
		{
			printf(", ");
		}
	}
	printf(" ]\n\n");
}

