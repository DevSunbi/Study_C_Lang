#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <string.h>

int main(void)
{
	char fruit[20] = "strawberry";
	strcpy(fruit, "banananananananananananana");

	printf("word => %s\n", fruit);

	return 0;
}