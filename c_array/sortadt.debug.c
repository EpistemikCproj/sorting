/* sortADT.c - various sorting algorithms */

#include "sortADT.dyn.h"

BOOLEAN IsSorted(SortingArray A, KEY n)
  {
	KEY i ;
	for ( i = 1; i <= n; i++ )
		if ( A[i] < A[i - 1] ) return False ;
	return True ;
  }

void Swap(KEY* i, KEY* j)
  {
	KEY temp;
	temp = *i ;
	*i = *j ;
	*j = temp ;
  }

/***************** SELECTION SORT *************************/

KEY Smallest(SortingArray L, KEY a, KEY b)
  {
	KEY k, SmallValue, SmallIndex ;
	SmallValue = L[a] ;
	SmallIndex = a ;
	if ( a < b )
	  {
		for (k = a+1; k <= b; k++)
			if ( L[k] < SmallValue )
			  {
				SmallValue = L[k] ;
				SmallIndex = k ;
			  }
	  }
	return SmallIndex ;
  }

void SelectionSort(SortingArray S, KEY n)
  {
	KEY j, k ;
	for (j = 0; j <= n; j++)
	  {
		k = Smallest(S, j, n) ;
		Swap( &S[k], &S[j] ) ;
	  }
  }

/********************** HEAP SORT *******************************/

/* SiftUp()
preconditions: A is an array, [i..n] is the range to be reheapified.
postconditions: A[i..n] has been reheapified */
void SiftUp(SortingArray A, KEY i, KEY n)
  {
	KEY j, RootKey ;
	BOOLEAN Finished ;

	RootKey = A[i];
	j = 2*(i+1) - 1 ;
	Finished = ( j > n ) ;

	while ( !Finished )
	  {
		if ( j <= n )
		  if ( A[j+1] > A[j] ) j++ ;

		if ( A[j] <= RootKey )
		  Finished = True ;
		else
		  {
			A[i] = A[j] ;
			i = j ;
			j = 2*(i+1) - 1 ;
			Finished = ( j > n) ;
		  }  /* else */
	  } /* while */
	A[i] = RootKey ;
  }

/* HeapSort()
preconditions: A is an array of size n storing values of type KeyType
postconditions: A has been sorted using the HeapSort algorithm found in program 13.10 */
void HeapSort(SortingArray A, KEY n)
  {
	KEY i ;

	for ( i = (n+1)/2; i >= 1; i-- )
		SiftUp(A, i-1, n);

	for ( i = n; i >= 1; i-- )
	  {
		SiftUp(A, 0, i) ;
		Swap( &A[0], &A[i] ) ;
	  }
  }

/*********************** QUICK SORT ***************************/

/* Partition()
preconditions: A is an array, and [i..j] is a range of values to be partitioned
postconditions: A[i..j] has been partitioned */
void Partition(SortingArray A, KEY *i, KEY *j)
  {
	KEY Pivot = A[ (*i + *j)/2 ] ;
	printf( "0. Pivot == %u, i == %u, j == %u \n", Pivot, *i, *j );
	do {
		 while ( A[*i] < Pivot ) (*i)++ ;
	printf( "1. Pivot == %u, i == %u, j == %u \n", Pivot, *i, *j );
		 while ( A[*j] > Pivot ) (*j)-- ;
	printf( "2. Pivot == %u, i == %u, j == %u \n", Pivot, *i, *j );
		 if ( *i <= *j )
			{
			 Swap( &A[*i], &A[*j] ) ;
	printf( "3. Pivot == %u, i == %u, j == %u \n", Pivot, *i, *j );
			 (*i)++ ;
			 (*j)-- ;/* IF j == 0 HERE, AND IF KEYS ARE UNSIGNED,
							THEN DECREMENTING j MAKES IT GO TO MAXINT !!!
							j WILL NOT BE > i FOR A LONG TIME...
							THE WHILE LOOP KEEPS RUNNING AND i GETS INCREMENTED
							PAST THE NORMAL END OF THE ARRAY UNTIL IT ACCESSES
							MEMORY SOMEWHERE THAT CRASHES THE PROGRAM.
							WE DO NOT HAVE THIS PROBLEM WITH PASCAL (OR C IF 1 IS
							USED AS THE BASE INDEX), AS j WILL DECREMENT TO ZERO
							AND THE WHILE LOOP TEST WILL END AS IT IS SUPPOSED TO.
			          */
	printf( "4. Pivot == %u, i == %u, j == %u \n", Pivot, *i, *j );
			}
		} while (*i <= *j) ;
  }

/* QuickSort()
preconditions: A is an array, and [m..n] is a range of values to be sorted
postconditions: A[m..n] has been sorted */
void QuickSort(SortingArray A, KEY m, KEY n)
  {
	KEY i, j ;
	if ( m < n )
	  {
		i = m ;  j = n ;
	printf( "Partition( A(%p), i(%u), j(%u) \n", &A, i, j );
		Partition(A, &i, &j) ;
	printf( "1. QuickSort( A(%p), m(%u), j(%u) \n", &A, m, j );
		QuickSort(A, m, j) ;
	printf( "2. QuickSort( A(%p), i(%u), n(%u) \n", &A, i, n );
		QuickSort(A, i, n) ;
	  }
  }

/*********************** RADIX SORT ************************/
/* RadixSort()
preconditions: A is an array of size n
postconditions: A[1..n] has been sorted using the RadixSort algorithm */
void RadixSort(SortingArray A, KEY n)
  {
	KEY temp, i, j, k, l ;
	Queue Qarray[20] ;

	for ( j = 0; j < 20; j++ ) CreateQ(&Qarray[j]) ;

	for ( j = 0; j <= n; j++ ) Enq(&Qarray[A[j] % 10], A[j]) ;

	for ( i = 1; i < 5; i++ )
	  {
		k = 0 ;
		for ( j = 0; j < 10; j++ )
		  {
			l = j ;
			if ( i % 2 == 0 )
			  l = j + 10 ;
			else k = 10 ;
			while ( !IsEmpty(&Qarray[l]) )
			  {
				temp = Deq(&Qarray[l]) ;
				Enq(&Qarray[(temp / (KEY) pow(10, i) % 10) + k], temp) ;
			  }  /* while */
		  }  /* for j */
	  }  /* for i */

	k = 0 ;
	for ( j = 0; j < 4; j++ )
		while ( !IsEmpty(&Qarray[j]) )
		  {
			A[k] = Deq(&Qarray[j]) ;
			k++ ;
		  }  /* while */
  }  /* RadixSort */

/* ====================== Big Radix Sort =========================== */

void BigRadixSort(SortingArray A, KEY n)
  {
	KEY temp, j, k ;  /* loop indices */
	Queue QarrM[D1_MAX] ;
	Queue QarrC[QMAX] ;

	for ( j = 0; j < D1_MAX; j++ ) CreateQ(&QarrM[j]) ;

	for ( j = 0; j < QMAX; j++ ) CreateQ(&QarrC[j]) ;

	for ( j = 0; j <= n; j++ ) Enq(&QarrM[A[j] % D1_MAX], A[j]) ;

	for ( j = 0; j < D1_MAX; j++ )
		while ( !IsEmpty(&QarrM[j]) )
		  {
			temp = Deq(&QarrM[j]) ;
			Enq(&QarrC[temp / D1_MAX], temp) ;
		  }  /* for while */

	k = 0 ;
	for ( j = 0; j < QMAX; j++ )
		while ( !IsEmpty(&QarrC[j]) )
		  {
			A[k] = Deq(&QarrC[j]) ;
			k++ ;
		  }  /* for while */

  }  /* BigRadixSort */

/* ===================== Array Radix Sort ========================= */

void Load(RadixArray L, KEY j, KEY V, BOOLEAN *Overflow)
  {
	KEY k = 0 ;
	while ( L[j][k] != FLAG  &&  k < D2_MAX ) k++ ;
	if ( k > D2_MAX )
	  *Overflow = True ;
	else
	  {
		L[j][k] = V ;
		*Overflow = False ;
	  }
  }

KEY Take(RadixArray T, KEY j)
  {
	KEY TakeVal ;
	KEY k = 0 ;
	while ( T[j][k] == FLAG  &&  k < D2_MAX ) k++ ;
	if ( k < D2_MAX )
	  {
		TakeVal = T[j][k] ;
		T[j][k] = FLAG ;
	  }
	else
	  TakeVal = FLAG ;
	return TakeVal ;
  }

BOOLEAN Is_empty(RadixArray E, KEY j)
  {
	KEY k ;
	for ( k = 0; k < D2_MAX; k++ )
	  if ( E[j][k] != FLAG ) return False ;
	return True ;
  }

void ArrayRadixSort(SortingArray A, KEY n)
  {
	BOOLEAN Overflow ;
	KEY j, k ;  /* loop indices */
	static RadixArray Darray ;

	for ( j = 0; j < D1_MAX; j++ )
		for ( k = 0; k < D2_MAX; k++ )
			Darray[j][k] = FLAG ;

	for ( j = 0; j <= n; j++ )
		Load(Darray, A[j] % D1_MAX, A[j], &Overflow ) ;
	if ( Overflow ) fprintf(stderr, " >> WARNING: array 1 overflow !!" ) ;

	k = 0 ;
	for ( j = 0; j < D1_MAX; j++ )
		while ( !Is_empty(Darray, j) )
		  {
			A[k] = Take(Darray, j) ;
			k++ ;
		  }
	if ( k < n )
	  fprintf(stderr, " >> WARNING: loss of data at stage 1: k = %u, n = %u !!", k, n ) ;

	for ( j = 0; j <= n; j++ )
		Load(Darray, A[j] / 100, A[j], &Overflow ) ;
	if ( Overflow )
	  fprintf(stderr, " >> WARNING: array 2 overflow !!" ) ;


	k = 0 ;
	for ( j = 0; j < D1_MAX; j++ )
		while ( !Is_empty(Darray, j) )
		  {
			A[k] = Take(Darray, j) ;
			k++ ;
		  }
	if ( k < n )
	  fprintf(stderr, " >> WARNING: loss of data at stage 2: k = %u, n = %u !!", k, n ) ;

  }  /* ArrayRadixSort */
