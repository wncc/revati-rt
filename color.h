#ifndef COLORH
#define COLORH
#include "vector3.h"
#include <iostream>
using namespace std;

class color {

public:
	float r;
	float g;
	float b;
	color();
	color(float a, float b, float c);
	void print(const char* title);
};

color :: color(){
	
}

color :: color(float a, float b, float c){
	r = a;
	g = b;
	b = c;
}

void color :: print(const char* title){
	printf("\t%s(color): (%f,%f,%f)\n", title, r, g, b);
}

#endif