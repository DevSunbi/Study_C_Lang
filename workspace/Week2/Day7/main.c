//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

int main(void) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int* pi = NULL;
	double* pd = NULL;

	pi = (int*)malloc(sizeof(int));
	if (pi == NULL)
	{
		printf("failed");
		exit(1);
		//return 1;
		//exit(-1);
	}

	pd = (double*)malloc(sizeof(double));
	if (pd == NULL)
	{
		printf("failed");
		exit(-1);
	}

	*pi = 10;
	*pd = 1.4;

	printf("%d %lf\n", *pi, *pd);

	//free(pi);
	//pi = NULL;
	//free(pd);
	//pd = NULL;

	//printf("%d \n", *pi);

	return 0;
}