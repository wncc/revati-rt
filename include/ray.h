#include "vector3.h"

#pragma once
using namespace std;

class ray {
	
	public:
		vector3 origin;
		vector3 direction;
		double min_t;
		double max_t;
		ray();
		ray(vector3 Origin, vector3 Direction, double Min_t, double Max_t);
		vector3 get_origin() const;
		vector3 get_direction() const;
		double get_max_t() const;
		double get_min_t() const;
		vector3 pointAt(double t) const;
};