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