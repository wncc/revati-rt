#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class vector3 {

	private:
		double v[3];
	public:
		vector3();
		vector3(double x, double y, double z);
		double x() const;
		double y() const;
		double z() const;
		double length() const;
		void unit_vector();
		vector3 unit() const;
		vector3 operator-() const;
		vector3 operator+(const vector3 &v1) const;
		vector3 operator-(const vector3 &v1) const;
		vector3 operator*(const vector3 &v1) const;
		vector3 operator*(double t) const;
		vector3 operator/(double t) const;
		vector3 cross(const vector3 &v1) const;
		double dot(const vector3 &v1) const;
		void print(ostream &stream) const;		
};
