#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "rental.h"
#include "sort.h"

extern bool parseArguments( int argc, char *argv[], bool *pbReverse, SORT_METHOD *peSortMethod, int *pnNumResults, int *pnMin, int *pnMax );

int main( int argc, char *argv[] )
{
    bool isReverse	= true;
    SORT_METHOD eSortMethod = -1;
    int nNumResults = 0;
    int nMin = 0;
    int nMax = 0;

    parseArguments( argc, argv, &isReverse, &eSortMethod, &nNumResults, &nMin, &nMax );

    RentalProperty properties[] = {
	{ 1, "Sussex", 0, 0 },
	{ 5, "Sussex", 0, 0 },
	{ 24, "Sussex", 0, 0 },
	{ 10, "Turtle Boulevard", 0, 0 },
	{ 5, "Snake Street", 0, 0 },
	{ 77, "Frog Court", 0, 0 },
	{ 33, "Fish Lane", 0, 0 },
	{ 18, "Robin Road", 0, 0 },
	{ 20, "Newt Road", 0, 0 },
	{ 1, "Salamander Street", 0, 0 },
	{ 1, "Robin Road", 0, 0 },
	{ 7, "Dragonfly Avenue", 0, 0 },
    };

    randomizeProperties( properties );

    sort( properties, eSortMethod );
    printList( properties, eSortMethod, isReverse, nNumResults, nMin, nMax );

    return EXIT_SUCCESS;
}
