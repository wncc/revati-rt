#ifndef IMAGEH
#define IMAGEH
#include "color.h"
#include <iostream>
using namespace std;

class image{

public:
	double width;
	double height;
	color bgcolor;
	image();
	void print();
};

image :: image(){
	
}

void image :: print(){
	printf("IMAGE-\n");
	printf("\twidth: %f\n", width);
	printf("\theight: %f\n", height);
	bgcolor.print("bgcolor");
}

#endif