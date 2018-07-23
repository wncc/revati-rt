#pragma once
#include "vector3.h"
#include "color.h"
#include <iostream>
using namespace std;

class light {
	
	private:
		vector3 position;
		color clr;
		double ka;
	public:
		light();
		light(vector3 Position, color Clr, double Ka);
		vector3 get_position() const;
		color get_clr() const;
		double get_ka() const;
		void print(ostream &stream) const;
};

