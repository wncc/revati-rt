#pragma once
#include "vector3.h"
#include "material.h"
#include "ray.h"
#include <iostream>
using namespace std;

class object {
	
	public:
		object();
		virtual vector3 get_normal(vector3 v1) const=0;
		virtual material* get_material() const=0;
		virtual bool intersect(double& t, ray camera_ray) const=0;
		virtual void print(ostream &stream) const=0;
};
