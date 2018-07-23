#include <vector3.h>

vector3 :: vector3(){

}

vector3 :: vector3(double x, double y, double z){
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

double vector3 :: x() const{
	return v[0];
}

double vector3 :: y() const{
	return v[1];
}

double vector3 :: z() const{
	return v[2];
}

double vector3 :: length() const{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

void vector3 :: unit_vector(){
	double n = length();
	v[0] /= n;
	v[1] /= n;
	v[2] /= n;
}

vector3 vector3 :: unit() const{
	double n = length();
	return vector3(v[0]/n, v[1]/n, v[2]/n);
}

vector3 vector3 :: operator-() const{
	return vector3(-v[0], -v[1], -v[2]);
}

vector3 vector3 :: operator+(const vector3 &v1) const{
	return vector3(v[0]+v1.v[0], v[1]+v1.v[1], v[2]+v1.v[2]);
}

vector3 vector3 :: operator-(const vector3 &v1) const{
	return vector3(v[0]-v1.v[0], v[1]-v1.v[1], v[2]-v1.v[2]);
}

vector3 vector3 :: operator*(const vector3 &v1) const{
	return vector3(v[0]*v1.v[0], v[1]*v1.v[1], v[2]*v1.v[2]);
}

vector3 vector3 :: operator*(double t) const{
	return vector3(t*v[0], t*v[1], t*v[2]);
}

vector3 vector3 :: operator/(double t) const{
	return vector3(v[0]/t, v[1]/t, v[2]/t);
}

double vector3 :: dot(const vector3 &v1) const{
	return v[0]*v1.v[0] + v[1]*v1.v[1] + v[2]*v1.v[2];
}

vector3 vector3 :: cross(const vector3 &v1) const{
	return vector3(v[1]*v1.v[2]-v[2]*v1.v[1], v[0]*v1.v[2]-v[2]*v1.v[0], v[0]*v1.v[1]-v[1]*v1.v[0]);
}

void vector3 :: print(ostream &stream) const{
	stream << "\t(" << v[0] << "," << v[1] << "," << v[2] << ")\n";
}