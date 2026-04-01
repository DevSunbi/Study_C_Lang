#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<crtdbg.h>
#include<stdlib.h>
#include "point.h"
#include "line.h"

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Line a = { {1, 2}, {5, 6} };
	Point b;

	return 0;
}