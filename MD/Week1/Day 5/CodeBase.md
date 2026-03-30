### 실습 1
```C
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

int main(void)
{
	int c = 100;
	int* pb = &c;
	int** pa = &c;
	**pa = 200;
	printf("%d\n", **pa);
	printf("%d\n", *pb);
	return 0;
}
```
=> 실 변수의 값을 주소로 읽으려 시도 -> 컴파일러가 강제로 프로그램 종료(보안 위험)
pa가 &c의 주소를 읽고 내부 변수의 값(100)을 다시 주소로 읽으려 함 -> 메모리 접근 허용 안됨

---
### 실습2
```C
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

int main(void)
{
	int a = 10, b = 15, total;
	double avg;
	int* pa, * pb;
	int* pt = &total;
	double* pg = &avg;

	pa = &a;
	pb = &b;
	*pt = *pa + *pb;
	*pg = *pt / 2.0;

	return 0;
}
```
![[Pasted image 20260327102134.png]]
-> pointer들의 값이 주소값이 부여됨을 볼 수 있음
![[Pasted image 20260327102437.png]]

---
### 실습 3
```C
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

int main(void)
{
	int a = 10, b = 15, total;
	double avg;
	const int* pa, * pb;
	int* pt = &total;
	double* pg = &avg;

	pa = &a;
	*pa = 20;
	pa = &b;
	pb = &a;
	*pt = *pa + *pb;
	*pg = *pt / 2.0;

	printf("%d, %x\n", *pa, pa);

	return 0;
}
```
![[Pasted image 20260327105049.png]]
-> const 포인터 변수의 값을 간접 수정하려하니 const로 인해 수정 불가
수정하려면 직접 수정 진행해야함 (a=20;)

---
### 실습 4
```C
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

int main(void)
{
	int a = 10, b = 15, total;
	double avg;
	int* const pa;
	int* pb;
	int* pt = &total;
	double* pg = &avg;

	*pa = 20;
	pb = &a;
	
	*pt = *pa + *pb;
	*pg = *pt / 2.0;

	printf("%d, %x\n", *pa, pa);

	return 0;
}
```
![[Pasted image 20260327105246.png]]
포인터 변수에 const 적용 -> 초기화 필수임(정적 할당)

---
### 실습5
```C
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

void swap(int x, int y);
void pointer_swap(int* x, int* y);

int main(void)
{
	int a = 10, b = 20;

	swap(a, b);
	printf("swap = %d, %d\n", a, b);
	pointer_swap(&a, &b);
	printf("pointer swap = %d, %d\n", a, b);
	return 0;
}

void swap(int x, int y) {
	printf("start swap func : %d, %d\n", x, y);
	int temp = x;
	x = y;
	y = temp;
	printf("end swap func : %d, %d\n", x, y);
}

void pointer_swap(int* x, int* y) {
	printf("start pointer swap func : %d, %d\n", *x, *y);
	int temp = *x;
	*x = *y;
	*y = temp;
	printf("start pointer swap func : %d, %d\n", *x, *y);
}
```
-> pointer param func는 여러 개의 값 수정 가능
-> param func는 하나의 값만 return 가능 -> 여러 개의 값 수정 불가함
=> 배열을 함수에 넘길 때 배열이 포인터 취급되는 이유
![[Pasted image 20260327114045.png]]

---
### 실습6
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print_ary(int*, int);

int main(void)
{
	int ary1[5] = { 10,20,30,40,50 };
	int ary2[7] = { 10,20,30,40,50,60,70 };

	int* ptr1 = &ary1;
	int* ptr2 = &ary2;

	int count = sizeof(ary1) / sizeof(ary1[0]);

	print_ary(ptr1, count);

	count = sizeof(ary2) / sizeof(ary2[0]);

	print_ary(ptr2, count);

	printf("\n");

	return 0;
}

void print_ary(const int* const pt, int size)
{

	for (int i = 0; i < size; i++) 
	{ 
		printf("%d ", pt[i]); 
	}
	printf("\n");
}
```
-> ptr로 사이즈 연산 수행 -> 주소는 무조건적으로 8byte => 짤려서 나옴 유의
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print_ary(int*, int);

int main(void)
{
	int ary1[5] = { 10,20,30,40,50 };
	int ary2[7] = { 10,20,30,40,50,60,70 };

	printf("%d \n", 5[ary2]);
```
=> 5[ary2] -> \*(5 + ary2)와 동일 취급 -> ary2[5]

---
### 실습7
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{	
	int i;
	printf("input number\n");
	scanf("input : %d", &i);
	printf("%d", i);

	return 0;
}
```
-> scanf에 타 문자열이 들어가면 해당 포맷에 맞춰 입력해야함
