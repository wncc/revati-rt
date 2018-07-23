#include <color.h>

color :: color(){
	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
}

color :: color(double r, double g, double b){
	c[0] = r;
	c[1] = g;
	c[2] = b;
}

double color :: r() const{
	return c[0];
}

double color :: g() const{
	return c[1];
}

double color :: b() const{
	return c[2];
}

color& color :: operator+=(const color &c1){
	c[0] += c1.c[0];
	c[1] += c1.c[1];
	c[2] += c1.c[2];
	return *this;	
}
		
color& color :: operator/=(double c1){
	c[0] /= c1;
	c[1] /= c1;
	c[2] /= c1;
	return *this;
}

color& color :: operator*=(const color &c1){
	c[0] *= c1.c[0];
	c[1] *= c1.c[1];
	c[2] *= c1.c[2];
	return *this;	
}

color color :: operator*(const color &c1) const{
	return color(c[0]*c1.c[0], c[1]*c1.c[1], c[2]*c1.c[2]);
}

color color :: operator*(double t) const{
	return color(c[0]*t, c[1]*t, c[2]*t);
}

void color :: clamp() {
    c[0] = max((double)0.0, min((double)1.0, c[0]));
    c[1] = max((double)0.0, min((double)1.0, c[1]));
    c[2] = max((double)0.0, min((double)1.0, c[2]));
}

void color :: print(ostream &stream) const{
	stream << "\t(" << c[0] << "," << c[1] << "," << c[2] << ")\n";
}