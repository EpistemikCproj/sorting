/* sortADT.c - various sorting algorithms */

#include "sortADT.h"

BOOLEAN IsSorted( SortingArray A, KEY n )
  {
	KEY i ;
	for( i = 2; i <= n; i++ )
		if( A[i] < A[i - 1] ) return False ;
	return True ;
  }

void Swap( KEY* i, KEY* j )
  {
	KEY temp;
	temp = *i ;
	*i = *j ;
	*j = temp ;
  }

/******************* SELECTION SORT ******************************/

KEY Largest( SortingArray A, KEY i, KEY j )
  {
	KEY k, BigVal, BigValKey ;
	BigVal = A[i] ;
	BigValKey = i ;
	if( i < j )
	  {
		for(k = i+1; k <= j; k++)
			if( A[k] > BigVal )
			  {
				BigVal = A[k] ;
				BigValKey = k ;
			  }
	  }
	return BigValKey ;
  }//Largest()

void SelectionSort( SortingArray S, KEY n )
  {
	KEY j, k ;
	for(j = n; j >= 2; j--)
	  {
		k = Largest(S, 1, j) ;
		Swap(&S[k], &S[j]) ;
	  }
  }//SelectionSort()

/********************** HEAP SORT ********************************/

/* SiftUp()
	preconditions:  A is an array, [i..n] is the range to be reheapified.
	postconditions: A[i..n] has been reheapified		*/
void SiftUp( SortingArray A, KEY i, KEY n )
  {
	KEY j, RootKey ;
	BOOLEAN Finished ;

	RootKey = A[i];
	j = 2 * i ;
	Finished = ( j > n ) ;

	while( !Finished )
	  {
		if( j < n )
		  if( A[j+1] > A[j] )
			 j++ ;

		if( A[j] <= RootKey )
		  Finished = True ;
		else
		  {
			A[i] = A[j] ;
			i = j ;
			j = 2 * i ;
			Finished = ( j > n) ;
		  }
	  }/* while */

	A[i] = RootKey ;
  }
// siftUp()

/* HeapSort()
	preconditions:  A is an array of size n storing values of type KeyType
	postconditions: A has been sorted using the HeapSort algorithm
						 found in program 13.10		*/
void HeapSort( SortingArray A, KEY n )
  {
	KEY i ;

	for( i = n/2; i >= 2; i-- )
		SiftUp(A, i, n);

	for( i = n; i >= 2; i-- )
	  {
		SiftUp( A, 1, i ) ;
		Swap( &A[1], &A[i] ) ;
	  }
  }
// HeapSort()

/*********************** QUICK SORT ***************************/

/* Partition()
	preconditions:  A is an array,
						 and [i..j] is a range of values to be partitioned
	postconditions: A[i..j] has been partitioned		*/
void Partition( SortingArray A, KEY *i, KEY *j )
  {
	KEY Pivot = A[ (*i + *j)/2 ] ;
	do
	  {
		while( A[*i] < Pivot )
			(*i)++ ;
		while( A[*j] > Pivot )
			(*j)-- ;
		if( *i <= *j )
		  {
			Swap( &A[*i], &A[*j] ) ;
			(*i)++ ;
			(*j)-- ;
		  }
	  } while( *i <= *j ) ;
  }
// Partition()

/* QuickSort()
	preconditions:  A is an array, and [m..n] is a range of values to be sorted
	postconditions: A[m..n] has been sorted	*/
void QuickSort( SortingArray A, KEY m, KEY n )
  {
	KEY i, j ;
	if( m < n )
	  {
		i = m ;  j = n ;
		Partition( A, &i, &j ) ;
		QuickSort( A, m, j ) ;
		QuickSort( A, i, n ) ;
	  }
  }

/************************** RADIX SORT ***************************/
/* RadixSort()
	preconditions:  A is an array of size n
	postconditions: A[1..n] has been sorted using the RadixSort algorithm	*/
void RadixSort( SortingArray A, KEY n )
  {
	KEY temp, i, j, k, l ;
	Queue Qarray[20] ;

	for( j = 0; j < 20; j++ )
	  CreateQ( &Qarray[j] ) ;

	for( j = 1; j <= n; j++ )
	  Enq( &Qarray[A[j] % 10], A[j] ) ;

	for( i = 1; i < 5; i++ )
	  {
		k = 0 ;
		for( j = 0; j < 10; j++ )
		  {
			l = j ;
			if( i % 2 == 0 )
			  l = j + 10 ;
			else
				 k = 10 ;
			while( !IsEmpty(&Qarray[l]) )
			  {
				temp = Deq( &Qarray[l] ) ;
				Enq( &Qarray[(temp / (KEY) pow(10, i) % 10) + k], temp ) ;
			  }
		  }/* for j */
	  }/* for i */

	k = 1 ;
	for( j = 0; j < 4; j++ )
		while( !IsEmpty(&Qarray[j]) )
		  {
			A[k] = Deq( &Qarray[j] ) ;
			k++ ;
		  }
  }/* RadixSort */

/* ======================= Big Radix Sort =========================== */

void BigRadixSort( SortingArray A, KEY n )
  {
	KEY temp, j, k ;  /* loop indices */
	Queue QarrM[1000] ;
	Queue QarrC[33] ;

	for( j = 0; j < 1000; j++ )
		CreateQ( &QarrM[j] ) ;

	for( j = 0; j < 33; j++ )
		CreateQ( &QarrC[j] ) ;

	for( j = 1; j <= n; j++ )
		Enq( &QarrM[A[j] % 1000], A[j] ) ;

	for( j = 0; j < 1000; j++ )
		while( !IsEmpty(&QarrM[j]) )
		  {
			temp = Deq( &QarrM[j] ) ;
			Enq( &QarrC[temp / 1000], temp ) ;
		  }

	k = 1 ;
	for( j = 0; j < 33; j++ )
		while( !IsEmpty( &QarrC[j] ) )
		  {
			A[k] = Deq( &QarrC[j] ) ;
			k++ ;
		  }
  }/* BigRadixSort */

/* ===================== Array Radix Sort ========================= */

void Load( RadixArray L, KEY j, KEY V, BOOLEAN *Overflow )
  {
	KEY k = 1 ;
	while( L[j][k] != FLAG  &&  k < D2_MAX )
		k++ ;
	if( k > D2_MAX )
	  *Overflow = True ;
	else
		{
		 L[j][k] = V ;
		 *Overflow = False ;
		}
  }
// Load()

KEY Take( RadixArray T, KEY j )
  {
	KEY TakeVal ;
	KEY k = 1 ;
	while( T[j][k] == FLAG  &&  k < D2_MAX )
		k++ ;
	if( k <= D2_MAX )
	  {
		TakeVal = T[j][k] ;
		T[j][k] = FLAG ;
	  }
	else
		 TakeVal = FLAG ;
	return TakeVal ;
  }//Take()

BOOLEAN Is_empty( RadixArray E, KEY j )
  {
	KEY k ;
	for( k = 1; k <= D2_MAX; k++ )
	  if( E[j][k] != FLAG )
		 return False ;
	return True ;
  }//IsEmpty()

void ArrayRadixSort( SortingArray A, KEY n )
  {
	BOOLEAN Overflow ;
	KEY j, k ;  /* loop indices */
	static RadixArray Darray ;

	for( j = 0; j <= D1_MAX; j++ )
		for( k = 1; k <= D2_MAX; k++ )
			Darray[j][k] = FLAG ;

	for( j = 1; j <= n; j++ )
		Load( Darray, A[j] % 1000, A[j], &Overflow ) ;
	if( Overflow )
	  fprintf( stderr, " >> WARNING: array 1 overflow !!" ) ;

	k = 1 ;
	for( j = 0; j <= D1_MAX; j++ )
		while( !Is_empty(Darray, j) )
		  {
			A[k] = Take( Darray, j ) ;
			k++ ;
		  }
	if( k < n )
	  fprintf( stderr,
				  " >> WARNING: loss of data at stage 1: k = %u, n = %u !!",
				  k, n ) ;

	for( j = 1; j <= n; j++ )
		Load( Darray, A[j] / 100, A[j], &Overflow ) ;
	if( Overflow )
	  fprintf( stderr, " >> WARNING: array 2 overflow !!" ) ;

	k = 1 ;
	for( j = 0; j <= D1_MAX; j++ )
		while( !Is_empty(Darray, j) )
		  {
			A[k] = Take( Darray, j ) ;
			k++ ;
		  }
	if( k < n )
	  fprintf( stderr,
				  " >> WARNING: loss of data at stage 2: k = %u, n = %u !!",
				  k, n ) ;

  }/* ArrayRadixSort */
