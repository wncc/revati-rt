#pragma once
#include "color.h"
#include <iostream>																																				
#include <fstream>
using namespace std;

class image {

	private:
		float width;
		float height;
		color bgcolor;																																																																																																																																																																																																																																																																																																																																																							
		char* data;
	public:
		image();
		image(float Width, float Height, color Bgcolor);
		float get_width() const;
		float get_height() const;
		color get_bgcolor() const;
		color get_pixel(float x, float y) const;
		void set_pixel(float x, float y, color clr);
		void write(string filename) const;
		void print(ostream &stream) const;
};