#include <sphere.h>

sphere :: sphere(){
	
}

sphere :: sphere(material* Mat, vector3 Center, double Radius){
	mat = Mat;
	center = Center;
	radius = Radius;
}

material* sphere :: get_material() const{
	return mat;
}

vector3 sphere :: get_center() const{
	return center;
}

double sphere :: get_radius() const{
	return radius;
}

bool sphere :: intersect(double& t, ray camera_ray) const{
	vector3 oc = camera_ray.get_origin()-center;
	vector3 dir = camera_ray.get_direction();
	double a = dir.dot(dir);
	double b = oc.dot(dir);
	double c = oc.dot(oc) - radius*radius;
	double d = b*b - a*c;
	double epsilon = 0.00000001;

	if (d >= epsilon){
		t = (-b-sqrt(d))/a;
		if(t<camera_ray.get_max_t() && t>camera_ray.get_min_t()){
			return true;
		}
		t = (-b+sqrt(d))/a;
		if(t<camera_ray.get_max_t() && t>camera_ray.get_min_t()){
			return true;
		}
	}
	return false;
}

vector3 sphere :: get_normal(vector3 v1) const{
	return (v1 - center).unit();
}

void sphere :: print(ostream &stream) const{
	stream << "SPHERE" << endl;
	stream << "\tmaterial- " << endl;
	mat->print(stream);
	stream << "\tcenter- ";
	center.print(stream);
	stream << "\tradius- " << radius << endl;
}