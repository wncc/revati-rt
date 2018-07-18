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
		float fov;
		float near;
		float far;
	public:
		camera();
		camera(vector3 Lookat, vector3 Eye, vector3 Up, float Fov, float Near, float Far);
		vector3 get_lookat() const;
		vector3 get_eye() const;
		vector3 get_up() const;
		float get_fov() const;
		float get_near() const;
		float get_far() const;
		ray generate_ray(float x, float y, int w, int h);
		void print(ostream &stream) const;
};

