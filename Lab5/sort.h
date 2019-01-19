extern int compareByAddress( RentalProperty* a, RentalProperty* b );
extern int compareByRooms( RentalProperty* a, RentalProperty* b );
extern int compareByRent( RentalProperty* a, RentalProperty* b );
extern void swap( RentalProperty properties[], int i, int j );
extern void sort( RentalProperty properties[], SORT_METHOD eSortMethod );

extern Comparator comparators[];
