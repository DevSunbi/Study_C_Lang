#include <iostream>
using namespace std;

void swap(int &a, int &b); // prototype

int main()
{
	int a = 5;
	int b = 10;

	cout << "[main] before swap, a  : "<< a <<", b : " << b << endl <<endl;

	swap(a, b);

	cout << "[main] after swap, a  : " << a << ", b : " << b << endl << endl;

	return 0;
}

void swap(int &a, int &b)
{
	cout << "[swap] before swap, a  : " << a << ", b : " << b << endl;
	int tmp = a;
	a = b;
	b = tmp;
	cout << "[swap] after swap, a  : " << a << ", b : " << b << endl << endl;
}