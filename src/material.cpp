#include "material.h"

material :: material(){	
}

material :: material(string Id, color Ambient, color Diffuse, color Specular, color Reflect, color Transmit, double Eta, double N, bool Isreflect, bool Istransmit){
	id = Id;
	ambient = Ambient;
	diffuse = Diffuse;
	specular = Specular;
	reflect = Reflect;
	transmit = Transmit;
	eta = Eta;
	n = N;
	isreflect = Isreflect;
	istransmit = Istransmit;
}


string material :: get_id() const{
	return id;
}

double material :: get_eta() const{
	return eta;
}

double material :: get_n() const{
	return n;
}

bool material :: get_istransmit() const{
	return istransmit;
}

bool material :: get_isreflect() const{
	return isreflect;
}

color material :: get_transmit() const{
	return transmit;
}

color material :: get_diffuse() const{
	return diffuse;
}

color material :: get_ambient() const{
	return ambient;
}

color material :: get_specular() const{
	return specular;
}

color material :: get_reflect() const{
	return reflect;
}

void material :: print(ostream &stream) const{
	stream << "MATERIAL:" << endl;
	stream << "\tid- " << id << endl;
	stream << "\tambient- ";
	ambient.print(stream);
	stream << "\tdiffuse- ";
	diffuse.print(stream);
	stream << "\tspecular- ";
	specular.print(stream);
	stream << "\treflect- ";
	reflect.print(stream);
	stream << "\ttransmit- ";
	transmit.print(stream);
	stream << "\teta- " << eta << endl;
	stream << "\tn- " << n << endl;
	stream << "\tisreflect- " << isreflect << endl;
	stream << "\tistransmit- " << istransmit << endl;
}
