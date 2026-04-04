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