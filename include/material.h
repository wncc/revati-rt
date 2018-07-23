#pragma once
#include "color.h"
#include <string>
#include <iostream>
using namespace std;

class material {
	
	private:
		string id;
		color ambient;
		color diffuse;
		color specular;
		color reflect;
		color transmit;
		double eta;
		double n;
		bool isreflect;
		bool istransmit;
	public:
		material();
		material(string Id, color Ambient, color Diffuse, color Specular, color Reflect, color Transmit, double Eta, double N, bool Isreflect, bool Istransmit);
		string get_id() const;
		color get_ambient() const;
		color get_diffuse() const;
		color get_specular() const;
		color get_reflect() const;
		color get_transmit() const;
		double get_eta() const;
		double get_n() const;
		bool get_istransmit() const;
		bool get_isreflect() const;
		void print(ostream &stream) const;
};

