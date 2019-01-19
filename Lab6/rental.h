extern int getRent( RentalProperty *pRental );
extern int getRooms( RentalProperty *pRental );
extern void printProperty( RentalProperty* pProperty );
extern void printList( RentalProperty properties[], SORT_METHOD eSortMethod, bool isReverse, int nNumResults, int nMin, int nMax );
extern int countProperties( RentalProperty *pProperties );
