### 실습1
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 0;
	scanf("%d", a);
	printf("%d\n", a);
	return 0;
}
```
![[Pasted image 20260325103525.png]]

---
### 실습2
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a=0;
	scanf("%d", &a);
	printf("%d\n", a);
	return 0;
}
```
---
### 실습3
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 3;

	int modulo = a % b;

	printf("%d\n", modulo);
	return 0;
}
```
---
### 실습4
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = -3;

	int modulo = a % b;

	printf("%d\n", modulo);
	return 0;
}
```
``` bash
1
```
---
### 실습5
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = -3;

	int div = a / b;
	int modulo = a % b;

	printf("%d, %d\n", div , modulo);
	return 0;
}
```
---
### 실습 6
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = -10;
	int b = 3;

	int div = a / b;
	int modulo = a % b;

	printf("%d, %d\n", div , modulo);
	return 0;
}
```
```bash
-3, -1
```
=> 0을 향해 더해간다/빼간다라는 개념으로 접근, 따라서 나머지 음수 출력

---
### 실습7
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = -10;
	int b = -3;

	int div = a / b;
	int modulo = a % b;

	printf("%d, %d\n", div , modulo);
	return 0;
}
```
```bash
3, -1
```
=> 동일하게 Adder의 특성으로 인해 나머지 음수 출력

---
### 실습8
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum(int x, int y /*형식 인자*/);

int main(void)
{
	int a = 10, b = 20;
	int result = 0;

	result = sum(a, b/*Parameter(copy해 전달)*/); // call by value

	printf("%d\n", result);

	return 0;
}

int sum(int x, int y)
{
	int temp = 0;
	temp = x + y;
	return temp;
}
```
---
