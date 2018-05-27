#ifndef VEC3H
#define VEC3H
#include <iostream>
using namespace std;

class vector3 {

public:
	float x;
	float y;
	float z;
	vector3();
	vector3(float a, float b, float c);
	void print(const char* title);
};

vector3 :: vector3(){

}

vector3 :: vector3(float a, float b, float c){
	x = a;
	y = b;
	z = c;
}

void vector3 :: print(const char* title){
	printf("\t%s(vector): (%f,%f,%f)\n", title, x, y, z);
}

#endif