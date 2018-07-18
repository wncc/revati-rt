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
		float radius;
	public:
		sphere();
		sphere(material* Mat, vector3 Center, float Radius);
		material* get_material() const;
		vector3 get_center() const;
		float get_radius() const;
		bool intersect(hit_record& h, ray camera_ray) const;
		vector3 get_normal(vector3 v1) const;
		virtual void print(ostream &stream) const;
};
