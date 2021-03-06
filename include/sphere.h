#pragma once
#include "vector3.h"
#include "object.h"
#include "material.h"
#include "ray.h"
#include <iostream>
using namespace std;

class sphere : public object {

	private:
		material* mat;
		vector3 center;
		double radius;
	public:
		sphere();
		sphere(material* Mat, vector3 Center, double Radius);
		material* get_material() const;
		vector3 get_center() const;
		double get_radius() const;
		bool intersect(double& t, ray camera_ray) const;
		vector3 get_normal(vector3 v1) const;
		virtual void print(ostream &stream) const;
};
