#include <sphere.h>

sphere :: sphere(){
	
}

sphere :: sphere(material* Mat, vector3 Center, float Radius){
	mat = Mat;
	center = Center;
	radius = Radius;
}

vector3 sphere :: get_normal(vector3 v1) const{
	vector3 normal = v1 - center;
	normal.unit_vector();
	return normal;
}

material* sphere :: get_material() const{
	return mat;
}

vector3 sphere :: get_center() const{
	return center;
}

float sphere :: get_radius() const{
	return radius;
}

bool sphere :: intersect(hit_record& h, ray camera_ray) const{
	vector3 oc = camera_ray.get_origin()-center;
	float a = camera_ray.get_direction().dot(camera_ray.get_direction());
	float b = oc.dot(camera_ray.get_direction());
	float c = oc.dot(oc) - radius*radius;
	float d = b*b - a*c;

	if (d > 0){
		float t = (-b-sqrt(d))/a;
		if(t<camera_ray.get_max_t() && t>camera_ray.get_min_t()){
			h = hit_record((camera_ray.pointAt(t)-center)/radius,t);
			return true;
		}
		t = (-b+sqrt(d))/a;
		if(t<camera_ray.get_max_t() && t>camera_ray.get_min_t()){
			h = hit_record((camera_ray.pointAt(t)-center)/radius,t);
			return true;
		}
	}
	return false;
}

void sphere :: print(ostream &stream) const{
	stream << "SPHERE" << endl;
	stream << "\tmaterial- " << endl;
	mat->print(stream);
	stream << "\tcenter- ";
	center.print(stream);
	stream << "\tradius- " << radius << endl;
}