#pragma once
#include "vector3.h"
#include "object.h"
#include "material.h"
#include "ray.h"
#include <iostream>
using namespace std;

class cylinder : public object {

	private:
		material* mat;
		vector3 center;
		double radius;
		double height;
	public:
		cylinder();
		cylinder(material* Mat, vector3 Center, double Radius, double Height);
		material* get_material() const;
		vector3 get_center() const;
		double get_radius() const;
		double get_height() const;
		bool intersect(double& t, ray camera_ray) const;
		bool intersect_base(double& t, ray camera_ray, double h) const;
		vector3 get_normal(vector3 v1) const;
		virtual void print(ostream &stream) const;
};
