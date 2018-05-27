#ifndef MATERIALH
#define MATERIALH
#include "color.h"
#include <string>
#include <iostream>
using namespace std;

class material
{
public:
	const char* id;
	color diffuse;
	color specular;
	color reflect;
	color transmit;
	double eta;
	double n;
	bool isreflect;
	bool istransmit;
	material();
	void print();
};

material :: material(){
	
}

void material :: print(){
	printf("MATERIAL %s-\n", id);
	diffuse.print("diffuse");
	specular.print("specular");
	reflect.print("reflect");
	transmit.print("transmit");
	printf("\teta: %f\n", eta);
	printf("\tn: %f\n", n);
	printf("\tisreflect: %d\n", isreflect);
	printf("\tistransmit: %d\n", istransmit);
}

#endif