#include <color.h>

color :: color(){
	
}

color :: color(float r, float g, float b){
	c[0] = r;
	c[1] = g;
	c[2] = b;
}

float color :: r() const{
	return c[0];
}

float color :: g() const{
	return c[1];
}

float color :: b() const{
	return c[2];
}

color& color :: operator+=(const color &c1){
	c[0] += c1.c[0];
	c[1] += c1.c[1];
	c[2] += c1.c[2];
	return *this;	
}
		
color& color :: operator/=(float c1){
	c[0] /= c1;
	c[1] /= c1;
	c[2] /= c1;
	return *this;
}

color color :: operator*(const color &c1) const{
	return color(c[0]*c1.c[0], c[1]*c1.c[1], c[2]*c1.c[2]);
}

color color :: operator*(float t) const{
	return color(c[0]*t, c[1]*t, c[2]*t);
}

void color :: clamp() {
    c[0] = max((float)0.0, min((float)1.0, c[0]));
    c[1] = max((float)0.0, min((float)1.0, c[1]));
    c[2] = max((float)0.0, min((float)1.0, c[2]));
}

void color :: print(ostream &stream) const{
	stream << "\t(" << c[0] << "," << c[1] << "," << c[2] << ")\n";
}