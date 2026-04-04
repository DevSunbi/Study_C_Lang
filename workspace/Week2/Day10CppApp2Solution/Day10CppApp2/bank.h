#pragma once
class bank {
private: 
	int safe;

public:
	bank();
	void use_counter(int _in, int _out);

	int get_safe(); // getter
	void set_safe(int _in); // setter
};