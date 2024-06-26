// sorter.c ... sorting algorithm analysis
// Written by John Shepherd, April 2013

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Items
typedef int Item;
#define key(A) (A)
#define show(A) { printf("%02d",(A)); }
int less(Item, Item);
void swap(Item *, int, int);
void move(Item *, int, int);

// book-keeping functions
void usage(char *);

// functions on arrays of Items
void display(Item *, int, int);
bool isSorted(Item *, int, int);
void bubbleSort(Item *, int, int);
void insertionSort(Item *, int, int);
void mergeSort(Item *, int, int);
void quickSort(Item *, int, int);
void selectionSort(Item *, int, int);

// global(!) variables for monitoring
int ncompares = 0;
int nswaps = 0;
int nmoves = 0;
int *A; // array to be sorted
int N;  // number of elements

int main (int argc, char *argv[])
{ 
	int i;  // index
	int x;  // random number
	int s;  // starting value
	
	if (argc < 4) usage(argv[0]);
	N = atoi(argv[2]);
	// if (N < 5 || N > 90) usage(argv[0]);
	if (argc == 5) s = atoi(argv[4]);
	A = malloc(N*sizeof(int));
	assert(A != NULL);

	// generate data
	switch (argv[3][0]) {
	case 'A':
		// ascending sequence in range 01..99
		x = (s > 0) ? s : 1;
		for (i = 0; i < N; i++)
			A[i] = x++;
		break;
	case 'D':
		// descending sequence in range 01..99
		x = (s > 0) ? s : 99;
		for (i = 0; i < N; i++)
			A[i] = x--;
		break;
	case 'R':
		// random sequence in range 01..99
		srand(s > 0 ? s : 0);
		for (i = 0; i < N; i++)
			A[i] = 1 + rand()%99;
		break;
	default:
		usage(argv[0]);
		break;
	}
	printf("Before: "); display(A, 0, N-1);

	// sort data
	switch (argv[1][0]) {
	case 'b': bubbleSort(A, 0, N-1); break;
	case 'i': insertionSort(A, 0, N-1); break;
	case 'm': mergeSort(A, 0, N-1); break;
	case 'q': quickSort(A, 0, N-1); break;
	case 's': selectionSort(A, 0, N-1); break;
	default: usage(argv[0]); break;
	}

	// display results
	printf("After:  "); display(A, 0, N-1);
	printf("#compares: %d, #swaps: %d, #moves: %d\n",
	       ncompares, nswaps, nmoves);
	if (isSorted(A, 0, N-1))
		printf("OK\n");
	else
		printf("Fail\n");

	return 0;
}

// functions on Items

int less(Item x, Item y)
{
	ncompares++;
	return (key(x) < key(y));
}

int eq(Item x, Item y)
{
	ncompares++;
	return (key(x) == key(y));
}

void swap(Item a[], int i, int j)
{
	nswaps++;
	Item tmp = a[i]; a[i] = a[j]; a[j] = tmp;
}

void move(Item a[], int i, int j)
{
	nmoves++;
	a[i] = a[j];
}


// Book-keeping functions

void usage(char *prog)
{
	fprintf(stderr,
	        "Usage: %s Algo Size Dist [Seed]\n", prog);
	fprintf(stderr,
	        "Algo = b|i|m|q|s, Dist = A|D|R\n");
	exit(1);
}


// Functions on arrays of Items

// show a[lo..hi] on stdout
void display(Item a[], int lo, int hi)
{
	int i;
	for (i = lo; i <= hi; i++) {
		putchar(' ');
		show(a[i]);
	}
	putchar('\n');
}

// show A[0..N-1] on stdout
void monitor(char *label)
{
	printf("%s: ",label); display(A, 0, N-1);
}

// is a[lo..hi] sorted?
bool isSorted(Item a[], int lo, int hi)
{
	for (int i = lo; i < hi-1; i++)
		if (less(a[i+1],a[i])) return false;
	return true;
}


// Sorting Algorithms

// bubble sort
void bubbleSort(Item a[], int lo, int hi)
{
   int i, j, nswaps;
   for (i = lo; i < hi; i++) {
      nswaps = 0;
      for (j = hi; j > i; j--) {
         if (less(a[j], a[j-1])) {
            swap(a,j,j-1);
            nswaps++;
         }
      }
      if (nswaps == 0) break;
   }
}

// insertion sort
void insertionSort(int a[], int lo, int hi)
{
   int i, j, val;
   for (i = hi; i > lo; i--) {
      if (less(a[i],a[i-1])) swap(a,i,i-1);
   }
   monitor("Next");
   for (i = lo+2; i <= hi; i++) {
      val = a[i];
      for (j = i; less(val,a[j-1]); j--) {
         move(a,j,j-1);
      }
      a[j] = val;
      monitor("Next");
   }
}

// mergesort
#if 0
void merge(Item a[], int lo, int mid, int hi)
{
   int  i, j, k, nitems = hi-lo+1;
   Item *tmp = malloc(nitems*sizeof(Item));

   i = lo; j = mid+1; k = 0;
   while (i <= mid && j <= hi) {
     if (less(a[i],a[j]))
	    tmp[k++] = a[i++];
	 else
	    tmp[k++] = a[j++];
   }
   while (i <= mid) tmp[k++] = a[i++];
   while (j <= hi) tmp[k++] = a[j++];

   //copy back
   for (i = lo, k = 0; i <= hi; i++, k++)
      a[i] = tmp[k];
   free(tmp);
}
void mergeSort(Item a[], int lo, int hi)
{
   int mid = (lo+hi)/2; // mid point
   if (hi <= lo) return;
   mergeSort(a, lo, mid);
   mergeSort(a, mid+1, hi);
   merge(a, lo, mid, hi);
}
#else
// merge arrays a[] and b[] into c[]
// aN = size of a[], bN = size of b[]
void merge(Item a[], int aN, Item b[], int bN, Item c[])
{
   int i; // index into a[]
   int j; // index into b[]
   int k; // index into c[] 
   for (i = j = k = 0; k < aN+bN; k++) {
      if (i == aN)
         c[k] = b[j++];
      else if (j == bN)
         c[k] = a[i++];
      else if (less(a[i],b[j]))
         c[k] = a[i++];
      else
         c[k] = b[j++];
   }
}
void doMergeSort(Item a[], Item b[], int lo, int hi)
{
   if (lo >= hi) return;
   int mid = (lo+hi)/2;
   doMergeSort(b, a, lo, mid);
   doMergeSort(b, a, mid+1, hi);
   merge(b+lo, mid-lo+1, b+mid+1, hi-mid, a+lo);
}
void mergeSort(Item a[], int lo, int hi)
{
   int i;
   Item *aux = malloc((hi+1)*sizeof(Item));
   for (i = lo; i <= hi; i++) aux[i] = a[i];
   doMergeSort(a, aux, lo, hi);
   free(aux);
}
#endif

// quicksort
int partition(Item a[], int lo, int hi)
{
   Item v = a[lo];  // pivot
   int  i = lo+1, j = hi;
   for (;;) {
      while (less(a[i],v) && i < j) i++;
      while (less(v,a[j]) && j > i) j--;
      if (i == j) break;
      swap(a,i,j);
   }
   j = less(a[i],v) ? i : i-1;
   swap(a,lo,j);
   return j;
}

void quickSort(int a[], int lo, int hi)
{
   int i; // index of pivot
   printf("qsort(a,%d,%d)\n",lo,hi);
// if (hi-lo < 5) bubbleSort(a,lo,hi);
   if (lo >= hi) return;
   i = partition(a, lo, hi);
   monitor("After partition");
   quickSort(a, lo, i-1);
   monitor("After qsort(lo,piv)");
   quickSort(a, i+1, hi);
   monitor("After qsort(piv,hi)");

}

// selection sort
void selectionSort(int a[], int lo, int hi)
{
   int i, j, min;
   for (i = lo; i < hi; i++) {
      min = i;
      for (j = i+1; j <= hi; j++) {
         if (less(a[j],a[min])) min = j;
      }
      swap(a,i,min);
   }
}