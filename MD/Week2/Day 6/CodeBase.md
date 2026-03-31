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

---
### 실습 2
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[80] = "strawberry";
	char str2[80] = "apple";
	char* ps1 = "banana";
	char* ps2 = str2;

	//strcpy(ps1, "abcd");

	printf("%s %s\n", ps2, str2);
	strncpy(ps2, "abcd", 6);
	printf("%s %s\n", ps2, str2);
	
	return 0;
}
```
---
### 실습 3
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char animal[5][20];
	int i;
	int count;
	count = sizeof(animal) / sizeof(animal[0]);

	printf("total : %d 1st : %d 2nd : %d\n", sizeof(animal), sizeof(animal[0]), sizeof(animal[0][0]));
	
	return 0;
}
```
---
### 실습 4
```C
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
		scanf("%s", *(animal + i)); // 주소 연산에서 나온 base 크기 : 주소
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
```
![[Pasted image 20260330164752.png]]
animal + 1 시작주소이면서 덩어리를 20개씩 char[20]*
\*(animal +1)시작주소이면서 char 1개씩 char[20]
