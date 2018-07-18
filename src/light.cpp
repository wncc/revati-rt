#include "light.h"

light :: light(){
	
}

light :: light(vector3 Position, color Clr, float Ka){
	position = Position;
	clr = Clr;
	ka = Ka;
}

vector3 light :: get_position() const{
	return position;
}

color light :: get_clr() const{
	return clr;
}

float light :: get_ka() const{
	return ka;
}

void light :: print(ostream &stream) const{
	stream << "LIGHT- " << endl;
	stream << "\tposition- ";
	position.print(stream);
	stream << "\tcolor- ";
	clr.print(stream);
	stream << "\tka: " << ka << endl;
}