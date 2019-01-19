#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "rental.h"
#include "sort.h"

int getRent( RentalProperty *pRental )
{
    return pRental->rent;
}

int getRooms( RentalProperty *pRental )
{
    return pRental->rooms;
}

void randomizeProperties( RentalProperty properties[] )
{
    for ( int i = 0; i < NUM_PROPERTIES; i++ )
    {
	properties[i].rent = (rand()%9 + 4)*100;
	properties[i].rooms = rand()%4 + 1;
    }
}

void printProperty( RentalProperty* pProperty )
{
    printf( "%3d %-32s%8d %8d\n", pProperty->streetNumber, pProperty->streetName, pProperty->rooms, pProperty->rent );
}

void printList( RentalProperty properties[], SORT_METHOD eSortMethod, bool isReverse, int nNumResults, int nMin, int nMax )
{
    printf( "\nSorted by %s\n", comparators[eSortMethod].label );
    printf( "%-35s %8s %8s\n", "Address", "# Rooms", "Rent" );
    printf( "%-35s %8s %8s\n", "--------------------------", "-------", "-------" );

    int n = 0;
    for ( int i = 0; i < NUM_PROPERTIES; i++ )
    {
	RentalProperty *pRental = &properties[ isReverse ? NUM_PROPERTIES-i-1 : i ];

	if ( comparators[eSortMethod].pGetter != NULL )
	{
	    int nValue = (*comparators[eSortMethod].pGetter)( pRental );
	    if ( nValue < nMin || nValue > nMax )
		continue;
	}

	if ( ++n > nNumResults )
	    break;

	printProperty( pRental );
    }

    if ( n == 0 )
	printf( "(No results)\n" );
}

