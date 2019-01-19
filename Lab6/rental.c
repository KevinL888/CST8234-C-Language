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

void printProperty( RentalProperty* pProperty )
{
    printf( "%3d %-32s%8d %8d\n", pProperty->streetNumber, pProperty->streetName, pProperty->rooms, pProperty->rent );
}

int countProperties( RentalProperty *properties )
{
    int nCount = 0;

    if ( properties != NULL )
    {
	while ( properties->rent >= 0 )
	{
	    nCount++;
	    properties++;
	}
    }

    return nCount;
}

void printList( RentalProperty properties[], SORT_METHOD eSortMethod, bool isReverse, int nNumResults, int nMin, int nMax )
{
    int nNumProperties = countProperties( properties );

    printf( "\nSorted by %s\n", comparators[eSortMethod].label );
    printf( "%-35s %8s %8s\n", "Address", "# Rooms", "Rent" );
    printf( "%-35s %8s %8s\n", "--------------------------", "-------", "-------" );

    int n = 0;
    for ( int i = 0; i < nNumProperties; i++ )
    {
	RentalProperty *pRental = &properties[ isReverse ? nNumProperties-i-1 : i ];

	if ( comparators[eSortMethod].pGetter != NULL )
	{
	    int nValue = (*comparators[eSortMethod].pGetter)( pRental );
	    if ( (nMin >= 0 && nValue < nMin) || (nMax >= 0 && nValue > nMax) )
		continue;
	}

	if ( nNumResults >= 0 && ++n > nNumResults )
	    break;

	printProperty( pRental );
	n++;
    }

    if ( n == 0 )
	printf( "(No results)\n" );
}
