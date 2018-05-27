#ifndef CAMERAH
#define CAMERAH
#include "vector3.h"
#include <iostream>
using namespace std;

class camera {

public:
	vector3 lookat;
	vector3 eye;
	vector3 up;
	float fov;
	double near;
	double far;
	camera();
	void print();
};

camera :: camera(){

}

void camera :: print(){
	printf("CAMERA-\n");
	lookat.print("lookat");
	eye.print("eye");
	up.print("up");
	printf("\tfov: %f\n", fov);
	printf("\tnear: %f\n", near);
	printf("\tfar: %f\n", far);
}

#endif