#include "integrator.h"

whitted_integrator :: whitted_integrator(int d)
{
	depth = d;
}

void integrator :: print(ostream &stream) const{
	stream << "INTEGRATOR: " << endl;
	stream << "\tdepth- " << depth << endl;
}

int integrator :: get_depth() const{
	return depth;
}

