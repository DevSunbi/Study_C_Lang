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