#pragma once
#include "vector3.h"
#include "material.h"
#include "ray.h"
#include <iostream>
using namespace std;

typedef pair<vector3, float> hit_record; 

class object {
	
	public:
		object();
		virtual vector3 get_normal(vector3 v1) const=0;
		virtual material* get_material() const=0;
		virtual bool intersect(hit_record& h, ray camera_ray) const=0;
		virtual void print(ostream &stream) const=0;
};
