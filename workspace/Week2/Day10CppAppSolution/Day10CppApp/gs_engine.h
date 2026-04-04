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