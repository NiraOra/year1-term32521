#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* compare function
*/
int myCmp(int val1, int val2){
    if(val1 < val2) { return -1;}
    else if (val1 > val2) { return 1; }
    else { return 0; }
}

/**
* Pre: n > 0, array a with at least one element
* Post: ??
 **/

int processA(int *a, int n, int (*fp) (int, int)){

    int cur = a[0];

	for(int i=1; i<n; i++){
        if( fp (cur, a[i]) < 0){
            cur = a[i];
        }
	}
    return cur;
}

int main(int argc, char *argv[]) {
  
	int marksA[] = {67, 34, 81, 44, 19};

	int ans = processA (marksA, 5, myCmp);

	printf("ans is %d \n", ans);
    printf("------------------------------------- \n");

    return 0;
}

