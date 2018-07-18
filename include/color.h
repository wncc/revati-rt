#pragma once
#include "vector3.h"
#include <iostream>
using namespace std;

class color {

	private:
		float c[3];
	public:
		color();
		color(float r, float g, float b);
		float r() const;
		float g() const;
		float b() const;
		void clamp();
		color& operator+=(const color &c1);
		color& operator/=(float c1);
		color operator*(const color &c1) const;
		color operator*(float t) const;
		void print(ostream &stream) const;
};
