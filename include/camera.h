#pragma once
#include "vector3.h"
#include "ray.h"
#include <iostream>
using namespace std;

class camera {

	private:
		vector3 lookat;
		vector3 eye;
		vector3 up;
		double fov;
		double near;
		double far;
	public:
		camera();
		camera(vector3 Lookat, vector3 Eye, vector3 Up, double Fov, double Near, double Far);
		vector3 get_lookat() const;
		vector3 get_eye() const;
		vector3 get_up() const;
		double get_fov() const;
		double get_near() const;
		double get_far() const;
		ray generate_ray(double x, double y, int w, int h);
		void print(ostream &stream) const;
};

