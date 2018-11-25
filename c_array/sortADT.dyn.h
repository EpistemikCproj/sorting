/* sortADT.h - various sorting algorithms */

#ifndef MHS_SORTADT_H
#define MHS_SORTADT_H

#include <math.h>
#include "queueADT.h"

//#define MAX 10000
#define D1_MAX 1000
#define D2_MAX 99
#define QMAX 37
#define FLAG -99

typedef int KEY ;
typedef KEY *SortingArray ;
typedef KEY RadixArray [D1_MAX][D2_MAX] ;

/************** FUNCTION  PROTOTYPES ****************/

BOOLEAN IsSorted(SortingArray, KEY);
void Swap(KEY*, KEY*);
KEY Largest(SortingArray, KEY, KEY);
void SelectionSort(SortingArray, KEY);
void SiftUp(SortingArray, KEY, KEY);
void HeapSort(SortingArray, KEY);
void Partition(SortingArray, KEY*, KEY*);
void QuickSort(SortingArray, KEY, KEY);
void RadixSort(SortingArray, KEY);
void BigRadixSort(SortingArray, KEY);
void Load(RadixArray, KEY, KEY, BOOLEAN*);
KEY Take(RadixArray, KEY);
BOOLEAN Is_empty(RadixArray, KEY);
void ArrayRadixSort(SortingArray, KEY);

#endif //__SORTADT_H__
