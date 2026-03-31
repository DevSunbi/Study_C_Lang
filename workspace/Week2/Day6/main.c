#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char animal[5][20];
	int i;
	int count;
	count = sizeof(animal) / sizeof(animal[0]);

	for (int i = 0; i < count; i++)
	{
		scanf("%s", *(animal + i));
	}
	
	for (int i = 0; i < count; i++)
	{
		printf("%s\n", *(animal + i));
		//puts("%s", * (animal + i));
		/**
		for (int j = 0; j < count; j++)
		{
			if (*(*(animal+i)+j) == '\0') break;
			printf("%c", *(*(animal + i)+j));
		}
		printf("\n");
		**/
	}

	return 0;
}