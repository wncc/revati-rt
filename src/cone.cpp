#include <cone.h>

cone :: cone(){
	
}

cone :: cone(material* Mat, vector3 Center, double Radius, double Height){
	mat = Mat;
	center = Center;
	radius = Radius;
	height = Height;
}

vector3 cone :: get_normal(vector3 v1) const{
	double r = sqrt((v1.x()-center.x())*(v1.x()-center.x()) + (v1.z()-center.z())*(v1.z()-center.z()));
    vector3 n = vector3 (v1.x()-center.x(), r*(radius/height), v1.z()-center.z());
    return n.unit();
}

material* cone :: get_material() const{
	return mat;
}

vector3 cone :: get_center() const{
	return center;
}

double cone :: get_radius() const{
	return radius;
}

double cone :: get_height() const{
	return height;
}

bool cone :: intersect(double& t, ray camera_ray) const{
	vector3 oc = camera_ray.get_origin()-center;
	vector3 dir = camera_ray.get_direction();
	double tan = (radius / height) * (radius / height);
    
    double a = dir.x()*dir.x() + dir.z()*dir.z() - tan*dir.y()*dir.y();
    double b = oc.x()*dir.x() + oc.z()*dir.z() + tan*(height-oc.y())*dir.y();
    double c = oc.x()*oc.x() + oc.z()*oc.z() - tan*(height-oc.y())*(height-oc.y());
    double d = b*b - a*c;
    bool hit = false;
    double epsilon = 0.00000001;
	double p;

    if (d >= epsilon){
    	double t1 = camera_ray.get_max_t();
    	double t2 = camera_ray.get_max_t();
		p = (-b-sqrt(d))/a;
		if(p<camera_ray.get_max_t() && p>camera_ray.get_min_t()){
			t1 = p;
		}
		p = (-b+sqrt(d))/a;
		if(p<camera_ray.get_max_t() && p>camera_ray.get_min_t()){
			t2 = p;
		}
		t = min(t1,t2);
		double y = oc.y() + t*dir.y();
		
	    if (y <= height && y >= 0.0){
			hit = true;
		}
	}
	return hit;
}

void cone :: print(ostream &stream) const{
	stream << "cone" << endl;
	stream << "\tmaterial- " << endl;
	mat->print(stream);
	stream << "\tcenter- ";
	center.print(stream);
	stream << "\tradius- " << radius << endl;
	stream << "\theight- " << height << endl;
}