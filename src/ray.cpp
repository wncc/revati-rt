#include "ray.h"

ray :: ray(){

}
	
ray :: ray(vector3 Origin, vector3 Direction, float Min_t, float Max_t){
	origin = Origin;
	direction = Direction;
	min_t = Min_t;
	max_t = Max_t;
}
	
vector3 ray :: get_origin() const{
	return origin;
}
	
vector3 ray :: get_direction() const{
	return direction;
}

float ray :: get_max_t() const{
	return max_t;
}
	
float ray :: get_min_t() const{
	return min_t;
}
	
vector3 ray :: pointAt(float t) const{
	return origin + direction*t;
}
