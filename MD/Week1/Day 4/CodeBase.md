### 실습 1
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char str1[80] = "cat";
	char str2[10];

	strcpy(str1, "tiger");
	strcpy(str2, str1);

	return 0;
}
```
---
### 실습 2
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char str1[80] = "cat";
	char str2[10];

	strcpy(str1, "tiger");
	strcpy(str2, str1);

	return 0;
}
```
---
### 실습 3
```C
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[80] = "cat";
	char str2[10];

	strcpy_s(str1, 80, "tiger");
	strcpy_s(str2, 80, str1);

	return 0;
}
```
![[Pasted image 20260326124401.png]]

---
### 실습 4
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	int ary[5];
	printf("total size : %zu\n", sizeof(ary));

	int i = 0;
	for (int i = 0; i < 0; i++)
	{
		printf("%d 번째 요소 : %d\n", i, ary[i]);
	}
	
	return 0;
}
```
```C
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <string.h>

int main(void)
{
	int ary[] = {0, 1, 2};

	printf("total size : %zu\n", sizeof(ary));

	int count = sizeof(ary) / sizeof(ary[0]);

	int i = 0;
	for (i = 0; i < count; i++)
	{
		printf("intdex:%d, value:%d\n", i, ary[i]);
	}
	
	return 0;
}
```
![[Pasted image 20260326141436.png]]
-> 0x000000... => Memory Address -> 배열의 이름 자체가 배열의 주소로 보임

---
### 실습 5
```C
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <string.h>

int main(void)
{
	char str[8] = {'a'}; // char str[8] = "a"; // char str[8] = {48};

	int i = 0;
	for (i = 0;i < 8;i++) 
	{
		printf("value : %c, ASCII : %d\n", str[i], str[i]);
	}

	return 0;
}
```
---
### 실습 6
```C
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <string.h>

int main(void)
{
	char str[8] = {48};

	scanf("%c", &str[0]); // 요소 입력 시 주소 기재 필수

	printf("%s\n", str);
	
	return 0;
}
```
![[Pasted image 20260326144856.png]]

---
### 실습 7
