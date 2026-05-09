```cpp title="engin.h"
#pragma once

class engine
{
public:
	
private:
	void acceleration_output();
	void reduce_output();
};
```
```Cpp title="ic_engine.h"
#pragma once
#include "engine.h"

class ic_engine : public engine // 상속 명시
{
public:

private:

	/* 선조 상속으로 인해 skip 가능 되려 선언 시 shadowing 문제좀 존재
	void accleration_output();
	void reduce_output();
	*/

};
```
```Cpp title="gs_engine.cpp"
#pragma once
#include "ic_engine.h"

class gs_engine : public ic_engine
{
private:
	int piston_speed;

	//void acceleration_output(); => 상속으로 인한 스킵 가능
	void increasing_fuel();
	void increasing_piston_speed();

public:
	void get_current_fuel();
};
```
```cpp title=gs_engine.pp
#include "gs_engine.h"

void gs_engine :: acceleration_output()
{

}

void gs_engine::increasing_fuel()
{

}

void gs_engine::increasing_piston_speed()
{

}

void gs_engine::get_current_fuel()
{

}
```
```cpp title=Day10CppApp.cpp
#include <iostream>
#include "gs_engine.h"
using namespace std;

int main()
{
	gs_engine my_engine;
	my_engine.get_current_fuel();

	gs_engine* ptr = new gs_engine();
	ptr->get_current_fuel();
	delete ptr;

	return 0;
}
```
---
### 실습 2
```cpp title="Day10CppApp2.cpp
#include <iostream>
#include "bank.h"
using namespace std;

int main()
{
	bank my_bank;

	my_bank.use_counter(0, 20);
	my_bank.use_counter(50, 0);
	my_bank.use_counter(100, 50);

	return 0;
}
```
```cpp title="bank.h"
#pragma once
class bank {
private: 
	int safe;

public:
	bank();
	void use_counter(int _in, int _out);
};
```
```cpp title="use_counter.cpp"
#include<iostream>
#include "bank.h"
using namespace std;

bank::bank() { // 생성자 함수
	safe = 1000;
	cout << "first bank : " << safe << endl;
	cout << endl;
}

void bank::use_counter(int _in, int _out) {
	safe += _in;
	safe += _out;

	cout << "bank in : " << _in << endl;
	cout << "bank out : " << _out << endl;
	cout << "bank : " << safe << endl;
	cout << endl;
}
```
