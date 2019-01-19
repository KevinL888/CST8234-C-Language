/********************************************************************************************************************
PROGRAM: Assignment1 - CST8234_013
AUTHOR: Kevin Lai, Xing Yi Wu, Greenish Kumar
DATE: Mar 16, 2018
PURPOSE: Header file to hold all function declarations for sort.c
*********************************************************************************************************************/

int differenceRoom(property *pStreetA, property *pStreetB);
int differenceRent(property *pStreetA, property *pStreetB);
int differenceAddress(property *pStreetA, property *pStreetB);
int differenceDistance(property *pStreetA, property *pStreetB);
void sort(node *pHead, int(*pComparator)(property *a, property *b));
void swap(node *pNode_A, node *pNode_B);
