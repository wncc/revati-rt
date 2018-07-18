#include "vector3.h"

#pragma once
using namespace std;

class ray {
	
	public:
		vector3 origin;
		vector3 direction;
		float min_t;
		float max_t;
		ray();
		ray(vector3 Origin, vector3 Direction, float Min_t, float Max_t);
		vector3 get_origin() const;
		vector3 get_direction() const;
		float get_max_t() const;
		float get_min_t() const;
		vector3 pointAt(float t) const;
};