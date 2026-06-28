### 실습 1
```C
int main(void)
{
	printf("Be Happy");
	return 0;
}
```
![[Pasted image 20260324101647.png]]

---
### 실습 2
```C
#include <stdio.h>

int main(void)
{
	printf("Be Happy");
	return 0;
}
```
---
### 실습 3
```C
#include <stdio.h>

int Main(void)
{
	printf("Be Happy");
	return 0;
}
```
![[Pasted image 20260324103205.png]]

---
### 실습 4
```C
#include <stdio.h>

int main(void)
{
	printf("Be Happy");
	printf("My Friend");
	return 0;
}
```
---
### 실습 5
```C
#include <stdio.h>

int main(void)
{
	short sh = 32767;
	printf("size=%lld\n", sizeof(sh));
	return 0;
}
```
---
### 실습 6
```C
#include <stdio.h>

int main(void)
{
	short sh = 32767;
	printf("size=%lld\n", sizeof(short));
	return 0;
}
```
---
### 실습 7
```C
#include <stdio.h>

int main(void)
{
	short sh = 32767;
	printf("size=%lld\n", sizeof(32767));
	return 0;
}
```
---
### 실습 8
```C
#include <stdio.h>

int main(void)
{
	short sh = 32768;
	printf("size=%lld\n", sizeof(sh));
	return 0;
}
```
---
### 실습 9
```C
#include <stdio.h>

int main(void)
{
	short sh = 32768;
	printf("size=%ld, sh=%d\n", sizeof(sh), sh);
	return 0;
}
```
---
### 실습 10
```C
#include <stdio.h>

int main(void)
{
	short sh = 32767;
	int in = 2147483647;
	long ln = 2147483647;
	long long lln = 123451234512345;

	printf("size=%lld, sh=%d\n", sizeof(sh), sh);
	printf("size=%lld, in=%d\n", sizeof(in), in);
	printf("size=%lld, ln=%ld\n", sizeof(ln), ln);
	printf("size=%lld, lln=%lld\n", sizeof(lln), lln);

	return 0;
}
```
```bash
size=2, sh=32767
size=4, in=2147483647
size=4, ln=2147483647
size=8, lln=123451234512345
```
---
### 실습 11
```C
#include <stdio.h>

int main(void)
{
	signed short sh = 32768;
	int in = 2147483647;
	long ln = 2147483647;
	long long lln = 123451234512345;
	
	printf("size=%lld, sh=%d\n", sizeof(sh), sh);
	printf("size=%lld, in=%d\n", sizeof(in), in);
	printf("size=%lld, ln=%ld\n", sizeof(ln), ln);
	printf("size=%lld, lln=%lld\n", sizeof(lln), lln);
	printf("size=%lld, size=%lld\n", sizeof(float), sizeof(double));


	return 0;
}
```
---
### 실습 12
```C
#include <stdio.h>

int main(void)
{
	unsigned int in = -1;
	unsigned short sh = -1;
	unsigned long ln = -1;
	unsigned long long lln = -1;
	float fl = -1;
	double db = -1;
	unsigned long int lin = -1;
	unsigned long long int llin = -1;
	long float lfl = -1;
	long double llfl = -1;
	unsigned char c = -1;

	printf("unsigned int = %u, size=%zu\n", in, sizeof(in));
	printf("unsigned short = %u, size=%zu\n", sh, sizeof(sh));
	printf("unsigned long = %u, size=%zu\n", ln, sizeof(ln));
	printf("unsigned long long = %llu, size=%zu\n", lln, sizeof(lln));
	printf("flaot = %f, size=%zu\n", fl, sizeof(fl));
	printf("double = %f, size=%zu\n", db, sizeof(db));
	printf("unsigned long int = %lu, size=%zu\n", lin, sizeof(lin));
	printf("unsinged long long int = %llu, size=%zu\n", llin, sizeof(llin));
	printf("long float = %lf, size=%zu\n", lfl, sizeof(lfl));
	printf("long double = %Lf, size=%zu\n", llfl, sizeof(llfl));
	printf("unsigned char = %u, size=%zu\n", c, sizeof(c));
	

}
```
```bash
unsigned int = 4294967295, size=4
unsigned short = 65535, size=2
unsigned long = 4294967295, size=4
unsigned long long = 18446744073709551615, size=8
flaot = -1.000000, size=4
double = -1.000000, size=8
unsigned long int = 4294967295, size=4
unsinged long long int = 18446744073709551615, size=8
long float = -1.000000, size=8
long double = -1.000000, size=8
unsigned char = 255, size=1
```
---
### 실습 13
```C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <string.h>

int main(void)
{
	char fruit[20]="strawberry";
	//strcpy(fruit, "strawberry");
	fruit[6] = '\0';

	printf("word => %s\n", fruit+30);

	return 0;
}
```
-> garbage 볼 수 있음
