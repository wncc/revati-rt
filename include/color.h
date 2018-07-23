#pragma once
#include "vector3.h"
#include <iostream>
using namespace std;

class color {

	private:
		double c[3];
	public:
		color();
		color(double r, double g, double b);
		double r() const;
		double g() const;
		double b() const;
		void clamp();
		color& operator+=(const color &c1);
		color& operator/=(double c1);
		color& operator*=(const color &c1);
		color operator*(const color &c1) const;
		color operator*(double t) const;
		void print(ostream &stream) const;
};
