#ifndef SPHEREH
#define SPHEREH
#include <string>
#include "vector3.h"
#include <iostream>
using namespace std;

class sphere {

public:
	const char* material;
	vector3 center;
	double radius;
	sphere();
	void print();
};

sphere :: sphere(){
	
}

void sphere :: print(){
	printf("SPHERE %s-\n",material);
	center.print("center");
	printf("\tradius: %f\n", radius);
}

#endif