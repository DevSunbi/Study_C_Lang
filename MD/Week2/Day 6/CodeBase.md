```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int num, grade;
	int res = 0;

	printf("ID Num : ");
	res = scanf("%d", &num);
	printf("Score : ");
	grade = getchar();
	printf("code : %d score : %c\n", num, grade);
	
	return 0;
}
```
=> buffer에 \n 들어가 있음 -> 버퍼에서 \n을 빼줘야 함
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int num, grade;
	int res = 0;

	printf("ID Num : ");
	res = scanf("%d", &num);
	getchar();
	printf("Score : ");
	grade = getchar();
	printf("code : %d score : %c\n", num, grade);
	
	return 0;
}
```
-> 위와 같이 수정해야 함