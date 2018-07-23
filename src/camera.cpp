#include <camera.h>

camera :: camera(){

}

camera :: camera(vector3 Lookat, vector3 Eye, vector3 Up, double Fov, double Near, double Far){
	lookat = Lookat;
	eye = Eye;
	up = Up;
	fov = Fov;
	near = Near;
	far = Far;
}

ray camera :: generate_ray(double x, double y, int w, int h){
	double Px = (2.0*(x/w)-1.0) * tan(fov/2.0) * w/h; 
	double Py = (1.0-2.0*y/h) * tan(fov/2.0); 
	vector3 direction = up.cross(lookat)*Px + up*Py + lookat;
	return ray(eye,direction,near,far);
}

vector3 camera :: get_lookat() const{
	return lookat;
}
		
vector3 camera :: get_eye() const{
	return eye;
}

vector3 camera :: get_up() const{
	return up;
}
		
double camera :: get_fov() const{
	return fov;
}
		
double camera :: get_near() const{
	return near;
}
		
double camera :: get_far() const{
	return far;
}
		
void camera :: print(ostream &stream) const{
	stream << "CAMERA- " << endl;
	stream << "\tlookat: ";
	lookat.print(stream);
	stream << "\teye: ";
	eye.print(stream);
	stream << "\tup: ";
	up.print(stream);
	stream << "\tfov: " << fov << "\n";
	stream << "\tnear: " << near << "\n";
	stream << "\tfar: " << far << "\n";
}

