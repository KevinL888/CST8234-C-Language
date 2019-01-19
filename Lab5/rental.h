#define 	NUM_PROPERTIES		12

extern int getRent( RentalProperty *pRental );
extern int getRooms( RentalProperty *pRental );
extern void randomizeProperties( RentalProperty properties[] );
extern void printProperty( RentalProperty* pProperty );
extern void printList( RentalProperty properties[], SORT_METHOD eSortMethod, bool isReverse, int nNumResults, int nMin, int nMax );
