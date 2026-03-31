### 실습 1
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) 
{
	int* pi = NULL;
	double* pd = NULL;

	pi = (int*)malloc(sizeof(int));
	if (pi == NULL)
	{
		exit(1);
		//return 1;
		//exit(-1);
	}

	pd = (int*)malloc(sizeof(double));
	if (pd == NULL)
	{
		exit(-1);
	}

	return 0;
}
```
![[Pasted image 20260331152253.png]]
* NULL 초기화 되어있음
![[Pasted image 20260331152356.png]]
![[Pasted image 20260331152433.png]]
![[Pasted image 20260331152501.png]]

---
### 실습 2
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
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

	free(pi);
	free(pd);

	return 0;
}
```
![[Pasted image 20260331153222.png]]
![[Pasted image 20260331153230.png]]

---
### 실습 3
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
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

	free(pi);
	free(pd);

	printf("%d \n", *pi);

	return 0;
}
```
![[Pasted image 20260331153311.png]]
* 아무튼 실행은 됐는데 안전한 값은 아님
* free 이후 초기화 값 넣어줌으로써 문제 발생 방지
* free 두 번 하면 실행 자체가 안됨
	* valid space를 가리키기 때문에 문제 발생
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
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

	free(pi);
	pi = NULL;
	free(pd);
	pd = NULL;

	printf("%d \n", *pi);

	return 0;
}
```
-> 해결한 코드임 ㅇㅇ

---
### 실습 4
```C
#define _CRT_SECURE_NO_WARNINGS
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

	free(pi);
	pi = NULL;
	free(pd);
	pd = NULL;

	printf("%d \n", *pi);

	return 0;
}
```
* 누수 플래그 추가
* studio가 메모리 누수 지점 output 창에서 출력
Detected memory leaks!
Dumping objects ->
{91} normal block at 0x00000206EC091330, 8 bytes long.
 Data: <ffffff ?> 66 66 66 66 66 66 F6 3F 
{90} normal block at 0x00000206EC087D10, 4 bytes long.
 Data: <    > 0A 00 00 00 
Object dump complete.
=> 디버깅 모드에서만 사용 가능, release 모드에서는 확인 불가
