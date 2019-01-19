#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "rental.h"
#include "sort.h"
#include "file.h"

extern bool parseArguments( int argc, char *argv[], RentalProperty **ppProperties, bool *pisAppend );

int main( int argc, char *argv[] )
{
    bool		isAppend = false;
    RentalProperty	*pProperties = NULL;

    parseArguments( argc, argv, &pProperties, &isAppend );	// read the specified files

    writeProperties( "properties.out", pProperties, sortByRent, false, -1, -1, -1, isAppend );

    return EXIT_SUCCESS;
}
