#ifndef LIGHTH
#define LIGHTH
#include "vector3.h"
#include "color.h"
#include <iostream>
using namespace std;

class light{

public:
	vector3 position;
	color clr;
	double ka;
	light();
	void print();
};

light :: light(){
	
}

void light :: print(){
	printf("LIGHT-\n");
	position.print("position");
	clr.print("clr");
	printf("\tka: %f\n", ka);
}

#endif