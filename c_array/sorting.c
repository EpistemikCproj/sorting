/* sorting.c - Sorting Comparisons - converted from Pascal */

#include <time.h>
#include "sortADT.dyn.h"

/************** FUNCTION  PROTOTYPES ****************/

void MakeRandomArray(SortingArray*, KEY);
void PrintArray(SortingArray, KEY);

/******************* MAIN ***************************/

SortingArray A;   /* Array to sort */

KEY  ch, n,			/* Number of elements in array */
	  choice,   	/* User input */
	  i,         	/* counter */
	  t,         	/* Number of trials */
	  correct ;  	/* Number of correct runs */

int main(void)
 {
  do {
		puts("\n 1. HeapSort an array          \t\t 7. Multi-test HeapSort");
		puts(" 2. QuickSort an array          \t 8. Multi-test QuickSort");
		puts(" 3. SelectionSort an array      \t 9. Multi-test SelectionSort");
		puts(" 4. RadixSort an array      \t\t10. Multi-test RadixSort");
		puts(" 5. BigRadixSort an array      \t\t11. Multi-test BigRadixSort");
		puts(" 6. ArrayRadixSort an array \t\t12. Multi-test ArrayRadixSort");
		puts("\t\t\t     99. QUIT \n");
		printf("Please choose an option: "),
		scanf("%u", &choice) ;

		if ( choice < 7 )
		  {
			puts("This option creates a random array and sorts it. ");
			printf("How many elements in the array: ") ;
			scanf("%u", &n) ;

			MakeRandomArray(&A, n) ;
			puts( "\n The random array: " ) ;
			if ( n <= 209 )
			  PrintArray(A, n) ;
			else fprintf(stdout, "%u ...array is TOO BIG to print... %u\n\n",A[0],A[n-1]) ;

			puts( "Press Enter to sort..." ) ;
			ch = getchar(); ch = getchar() ;

			switch (choice) {
				case  1: { HeapSort(A,n-1) ; break ; }
				case  2: { QuickSort(A,0,n-1) ; break ; }
				case  3: { SelectionSort(A,n-1) ; break ; }
				case  4: { RadixSort(A,n-1) ; break ; }
				case  5: { BigRadixSort(A,n-1) ; break ; }
				case  6: { ArrayRadixSort(A,n-1) ; break ; }
				}  /* switch */

			puts( " The sorted array: " );
			if ( n <= 209 )
			  PrintArray(A, n) ;
			else fprintf(stdout, "%u ...array is TOO BIG to print... %u\n\n",A[0],A[n-1]) ;

			printf( " Choice was %u, 'IsSorted' returned ", choice) ;
			IsSorted(A,n) ? puts("True.") : puts("False.") ;
		  }  /* if choice < 7 */

		else if (choice < 13)
		  {
			puts( "This option tests a sorting algorithm on a bunch of arrays. " );
			printf("How many elements in each array: ");
			scanf("%u", &n) ;
			printf("How many tests do you want to do: ");
			scanf("%u", &t) ;

			correct = 0 ;
			for ( i = 1; i <= t; i++ )
				{
				 MakeRandomArray(&A,n);
				 switch (choice) {
					case  7: { HeapSort(A,n-1) ; break ; }
					case  8: { QuickSort(A,0,n-1) ; break ; }
					case  9: { SelectionSort(A,n-1) ; break ; }
					case  10: { RadixSort(A,n-1) ; break ; }
					case  11: { BigRadixSort(A,n-1) ; break ; }
					case  12: { ArrayRadixSort(A,n-1) ; break ; }
					}  /* switch */

				 if ( IsSorted(A,n) ) correct++ ;
				}  /* for */

			printf("\n Choice was %u, 'IsSorted' returned True %u times in %u trials. \n",
					  choice, correct, t ) ;
		  }  /* else if choice < 13 */

	  } while ( choice != 99 ) ;

	if ( !MemCheck ) puts(" >> ERROR: Memory Leak! \n") ;

	puts("\t PROGRAM ENDED.") ;

	return 0;
 }//main()

/************ FUNCTION DEFINITIONS ********************/

/* MakeRandomArray()
preconditions: n is the size of array to create
postconds: A[1..n] has been initialized with random numbers in the range 1..MAXINT */
void MakeRandomArray(SortingArray *A, KEY N)
  {
	KEY i ;
	srand((unsigned int) time(0)); //randomize rand()
	*A = (KEY*) malloc(N * sizeof(KEY)) ;
	for ( i = 0; i < N; i++ )
		(*A)[i] = rand() % 9999 + 1 ;
  }

/* PrintArray()
preconditions: A is an array of size n
postconditions: A[1..n] is printed to the screen */
void PrintArray(SortingArray A, KEY N)
  {
	KEY j, k, size ;
	for ( j = 1; j <= (N / 11) + 1; j++ )
		{
		 if ( (j * 11) <= N )
			size = 11 ;
		 else
			size = N - ( (j - 1) * 11 ) ;
		 puts(" ") ;
		 for ( k = 0; k < size; k++ )
			 printf( "%6u", A[(j - 1) * 11 + k] ) ;
		 puts(" ") ;
		}
	if ( (N % 11) != 0 ) puts(" ") ;
  }  /* PrintArray */
