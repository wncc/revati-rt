#pragma once
#include "color.h"
#include <iostream>																																				
#include <fstream>
using namespace std;

class image {

	private:
		double width;
		double height;
		color bgcolor;																																																																																																																																																																																																																																																																																																																																																							
		char* data;
	public:
		image();
		image(double Width, double Height, color Bgcolor);
		double get_width() const;
		double get_height() const;
		color get_bgcolor() const;
		color get_pixel(double x, double y) const;
		void set_pixel(double x, double y, color clr);
		void write(string filename) const;
		void print(ostream &stream) const;
};