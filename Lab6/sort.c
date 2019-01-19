#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "rental.h"
#include "sort.h"

Comparator comparators[] = {
    { "Rent", &compareByRent, &getRent },
    { "Rooms", &compareByRooms, &getRooms },
    { "Address", &compareByAddress, NULL }
};

void swap( RentalProperty properties[], int i, int j )
{
    RentalProperty temp = properties[i];
    properties[i] = properties[j];
    properties[j] = temp;
}

int compareByAddress( RentalProperty* a, RentalProperty* b )
{
    int diff = strcmp( a->streetName, b->streetName );
    if ( diff == 0 )
	diff = a->streetNumber - b->streetNumber;
    return diff;
}

int compareByRooms( RentalProperty* a, RentalProperty* b )
{
    int diff = a->rooms - b->rooms;
    if ( diff == 0 )
	diff = a->rent - b->rent;
    return diff;
}

int compareByRent( RentalProperty* a, RentalProperty* b )
{
    int diff = a->rent - b->rent;
    if ( diff == 0 )
	diff = a->rooms - b->rooms;
    return diff;
}

void sort( RentalProperty properties[], SORT_METHOD eSortMethod )
{
    int nNumProperties = countProperties( properties );

    for ( int i = 0; i < nNumProperties - 1; i++ )
	for ( int j = 0; j < nNumProperties - i - 1; j++ )
	    if ( (*comparators[eSortMethod].pComparator)( &properties[j], &properties[j+1] ) > 0 )
		swap( properties, j, j+1 );
}
