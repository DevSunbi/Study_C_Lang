#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum(int x, int y);

int main(void)
{
	int a = 10, b = 20;
	int result = 0;

	result = sum(a, b);

	printf("%d\n", result);

	return 0;
}

int sum(int x, int y)
{
	int temp = 0;
	temp = x + y;
	return temp;
}