#pragma once
#include "scene.h"
#include <iostream>
using namespace std;

///Forward Declaration
class scene;

class integrator {

	public:
		int depth;
		int get_depth() const;
		void print(ostream &stream) const;
};

class whitted_integrator : integrator {
	
	public:
		whitted_integrator();
		whitted_integrator(int Depth);
};
