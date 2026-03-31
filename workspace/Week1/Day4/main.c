#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <string.h>

int main(void)
{
	char str[8] = {48};

	scanf("%c", &str[0]);

	printf("%s\n", str);
	
	return 0;
}