### 실습1
```C
#include <iostream>
using namespace std;

int main()
{
	float float_val = 1.5;
	double double_va = float_val;
	int int_val = (int)float_val;

	int_val = (int)3.5;

	return 0;
}
```
* 형 변환 시 casting operator 명시 해주는 것이 좋음
* 컴파일러가 용인 안해주는 경우 존재하기에 명시적 형변환 필요
* 아래는 형변환 안해준 경우
```bash
오전 9:36에 빌드를 시작함...
1>------ 빌드 시작: 프로젝트: ConsoleApplication2, 구성: Debug x64 ------
1>  ConsoleApplication2.cpp
1>C:\Users\Sunbi\source\repos\Day9CppApp\ConsoleApplication2\ConsoleApplication2.cpp(8,14): warning C4244: '초기화 중': 'float'에서 'int'(으)로 변환하면서 데이터가 손실될 수 있습니다.
1>C:\Users\Sunbi\source\repos\Day9CppApp\ConsoleApplication2\ConsoleApplication2.cpp(10,12): warning C4244: '=': 'double'에서 'int'(으)로 변환하면서 데이터가 손실될 수 있습니다.
========== 빌드: 1개 성공, 0개 실패, 0개 최신 상태, 0개 건너뜀 ==========
========== 빌드이(가) 오전 9:36에 완료되었으며, 00.921 초이(가) 걸림 ==========
```
---
### 실습2
```C
#include <iostream>
using namespace std;

void swap(int, int); // prototype

int main()
{
	int a = 5;
	int b = 10;

	cout << "[main] before swap, a  : "<< a <<", b : " << b << endl <<endl;

	swap(a, b);

	cout << "[main] after swap, a  : " << a << ", b : " << b << endl << endl;

	return 0;
}

void swap(int a, int b)
{
	cout << "[swap] before swap, a  : " << a << ", b : " << b << endl;
	int tmp = a;
	a = b;
	b = tmp;
	cout << "[swap] after swap, a  : " << a << ", b : " << b << endl << endl;
}
```
* call by value
