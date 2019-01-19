#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "rental.h"
#include "sort.h"
#include "file.h"

/***********************************************
 * Note, this function always exits the program!
 **********************************************/
void printHelpAndExit( char *strCommand, bool isError )
{
    if ( ! isError )
	printf( "\n%s - read some rental properties from file(s) and write them out to 'properties.out' after sorting.\n", strCommand );

    printf( "\nUsage: %s [OPTIONS] FILES\n\n", strCommand );
    printf( "Arguments:\n\n" );
    printf( "    -a, --append\t\tappend the results to the 'properties.out'\n" );
    printf( "    -h, --help\t\t\tPrint this message\n" );

    exit( isError ? EXIT_FAILURE : EXIT_SUCCESS );
}


bool parseArguments( int argc, char *argv[], RentalProperty **ppProperties, bool *pisAppend )
{
    // does the program name start with a local path specifier?
    char	*strCommand = argv[0];
    if ( strncmp( "./", strCommand, 2 ) == 0 )
	strCommand += 2;

    int nFiles = 0;

    for ( int iArg = 1; iArg < argc; iArg++ )
    {
	char *flag = argv[iArg];
	if ( strcmp( "-h", flag ) == 0 || strcmp( "--help", flag ) == 0 )
	    printHelpAndExit( strCommand, false );

	else if ( strcmp( "-a", flag ) == 0 || strncmp( "--append", flag, 8 ) == 0 )
	    *pisAppend = true;

	else 	// must be a filename we're reading
	{
	    if ( ! readProperties( argv[iArg], ppProperties ) )
	    {
		printf( "error processing filename '%s'\n", argv[iArg] );
		printHelpAndExit( strCommand, true );
	    }
	    nFiles++;
	}
    }

    if ( nFiles == 0 )	// did we do nothing?
    {
	printf( "You must provide same filename(s)\n" );
	printHelpAndExit( strCommand, true );
    }

    return true;
}
