// s.c ... one line description

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	//int i;
	int n = atoi(argv[1]);

	for (int i = 1; i <= n; i++)
		printf("%d ",i);
	printf("\n");
	return EXIT_SUCCESS;
}