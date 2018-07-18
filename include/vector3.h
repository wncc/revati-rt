#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class vector3 {

	private:
		float v[3];
	public:
		vector3();
		vector3(float x, float y, float z);
		float x() const;
		float y() const;
		float z() const;
		float length() const;
		void unit_vector();
		vector3 operator+(const vector3 &v1) const;
		vector3 operator-(const vector3 &v1) const;
		vector3 operator*(const vector3 &v1) const;
		vector3 operator*(float t) const;
		vector3 operator/(float t) const;
		vector3 cross(const vector3 &v1) const;
		float dot(const vector3 &v1) const;
		void print(ostream &stream) const;		
};
