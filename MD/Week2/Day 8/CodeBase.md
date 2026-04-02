### 실습1
``` C
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<crtdbg.h>
#include<stdlib.h>

#pragma pack(push, 1) // __attribute__((packed))
typedef struct 
{
	int num;
	double grade;
}student;

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	student s1 = { 315, 4.2 };

	printf("size = %d\n", sizeof(s1));

	return 0;

}
```
![[Pasted image 20260401104930.png]]
-> num과 grade 사이 정수 하나만큼의 차이 존재 확인 가능
=> pragma pack을 사용해서 padding을 제거 했음을 확인 가능(690)이 나와야 정상

---
### 실습2
```C
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<crtdbg.h>
#include<stdlib.h>

#pragma pack(push, 1) // __attribute__((packed))

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FILE* fp;
	int ary[10] = { 13, 10, 13, 13, 10, 26, 13, 10, 13, 10 };
	int i, res;

	fp = fopen("a.txt", "wb"); // open as bin -> 변형 없이 => txt 출력 시 변형 발생 가능

	for (i = 0;i < 10;i++)
	{
		fputc(ary[i], fp);
	}

	fclose(fp);
	fp = NULL;

	return 0;
}
```
![[Pasted image 20260401115719.png]]
![[Pasted image 20260401115737.png]]
![[Pasted image 20260401115921.png]]
-> 바이너리 편집기 내부 모습
```C
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<crtdbg.h>
#include<stdlib.h>

#pragma pack(push, 1) // __attribute__((packed))

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FILE* fp;
	int ary[10] = { 13, 10, 13, 13, 10, 26, 13, 10, 13, 10 };
	int i, res;

	fp = fopen("a.txt", "wb"); // open as bin -> 변형 없이 => txt 출력 시 변형 발생 가능

	for (i = 0;i < 10;i++)
	{
		fputc(ary[i], fp);
	}

	fclose(fp);

	fp = fopen("a.txt", "rb");

	while (1)
	{
		res = fgetc(fp);
		if (res == EOF) break;
		printf("%4d", res);
	}

	fclose(fp);
	fp = NULL;

	return 0;
}
```
=> fopen 후 close안하면 진입 불가 함 명시
