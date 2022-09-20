// testSet.c ... client to test Set ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Set.h"

int main(int argc, char *argv[])
{
	Set s1, s2;
	int i;
    
	s1 = newSet();
	for (i = 1; i < 6; i++) {
		SetInsert(s1,i);
	}

	s2 = newSet();
	for (i = 4; i < 10; i++) {
		SetInsert(s2,i);
	}

	printf("s1:"); showSet(s1); printf("\n");
	printf("s2:"); showSet(s2); printf("\n");

	// add more tests here ... 
	
	return 0;
}
