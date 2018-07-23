#include <cylinder.h>

cylinder :: cylinder(){
	
}

cylinder :: cylinder(material* Mat, vector3 Center, double Radius, double Height){
	mat = Mat;
	center = Center;
	radius = Radius;
	height = Height;
}

vector3 cylinder :: get_normal(vector3 v1) const{
	// Point is on one of the bases
	if (v1.x()<center.x()+radius && v1.x()>center.x()-radius && v1.z()<center.z()+radius && v1.z()>center.z()-radius){
		double epsilon = 0.000001;
		if (v1.y() < center.y()+height+epsilon && v1.y()>center.y()+height-epsilon){
			return vector3(0,1,0);
		}
		if (v1.y() < center.y()+epsilon && v1.y()>center.y()-epsilon){
			return vector3(0,-1,0);
		}
	}

	// Point is on lateral surface
	return vector3(v1.x()-center.x(),0,v1.z()-center.z()).unit();
}

material* cylinder :: get_material() const{
	return mat;
}

vector3 cylinder :: get_center() const{
	return center;
}

double cylinder :: get_radius() const{
	return radius;
}

double cylinder :: get_height() const{
	return height;
}

bool cylinder :: intersect(double& t, ray camera_ray) const{
	vector3 oc = camera_ray.get_origin()-center;
	vector3 dir = camera_ray.get_direction();
	double a = dir.x()*dir.x() + dir.z()*dir.z();
    double b = dir.x()*oc.x() + dir.z()*oc.z();
    double c = oc.x()*oc.x() + oc.z()*oc.z() - radius*radius;   
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
		
	    if (y >= height || y <= 0.0) {
			t1 = camera_ray.get_max_t();
    		t2 = camera_ray.get_max_t();
			if(intersect_base(p, camera_ray, 0)){
				if(p<camera_ray.get_max_t() && p>camera_ray.get_min_t()){
					hit = true;
					t1 = p;
				}
			}
			if(intersect_base(p, camera_ray, height)){
				if(p<camera_ray.get_max_t() && p>camera_ray.get_min_t()){
					hit = true;
					t2 = p;
				}
			}
			t = min(t,min(t1,t2));
		}
		else{
			hit = true;
		}
	}
	return hit;
}

bool cylinder :: intersect_base (double& t, ray camera_ray, double h) const{
	vector3 c = center + vector3(0,h,0);
	vector3 normal = get_normal(c);
	vector3 oc = camera_ray.get_origin()-center;
	vector3 dir = camera_ray.get_direction();
	bool hit = false;
    double A = normal.x();
	double B = normal.y();
	double C = normal.z();
	double D = - (A*(c.x()-center.x()) +B*(c.y()-center.y())+C*(c.z()-center.z()));

	if (A*dir.x()+B*dir.y()+C*dir.z()==0)
		return hit;
	
	t = - (A*oc.x()+B*oc.y()+C*oc.z()+D)/(A*dir.x()+B*dir.y()+C*dir.z());

	double epsilon = 0.00000001;
	vector3 p = oc + dir*t;
	if(t>=epsilon){
		if (p.x()*p.x()+p.z()*p.z()-radius*radius < epsilon)
			hit = true;
	}

	return hit;
}

void cylinder :: print(ostream &stream) const{
	stream << "cylinder" << endl;
	stream << "\tmaterial- " << endl;
	mat->print(stream);
	stream << "\tcenter- ";
	center.print(stream);
	stream << "\tradius- " << radius << endl;
	stream << "\theight- " << height << endl;
}