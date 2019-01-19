typedef enum SORT_METHOD {
    sortByRent = 0,
    sortByRooms = 1,
    sortByAddress = 2
} SORT_METHOD;

typedef struct {
    int		streetNumber;
    char*	streetName;
    int		rent;
    int		rooms;
} RentalProperty;

typedef struct {
    char	*label;
    int		(*pComparator)( RentalProperty *a, RentalProperty *b );
    int		(*pGetter)( RentalProperty *a );
} Comparator;
