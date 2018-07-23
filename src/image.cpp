#include<image.h>

image :: image(){
}

image :: image(double Width, double Height, color Bgcolor){
	width = Width;
	height = Height;
	bgcolor = Bgcolor;
	data = new char[int(width)*int(height)*3]; 
}

double image :: get_width() const{
	return width;
}

double image :: get_height() const{
	return height;
}

color image :: get_bgcolor() const{
	return bgcolor;
}

color image :: get_pixel(double x, double y) const{
	int pos=(y*width+x)*3;
	double r=double(data[pos])/255.0f;
	double g=double(data[pos+1])/255.0f;
	double b=double(data[pos+2])/255.0f;
	return color(r,g,b);
}
		
void image :: set_pixel(double x, double y, color clr){
	int pos=(y*width+x)*3;
	data[pos] = char(pow(clr.r(),1/2.2)*255+.5);
	data[pos+1] = char(pow(clr.g(),1/2.2)*255+.5);
	data[pos+2] = char(pow(clr.b(),1/2.2)*255+.5);
}

void image :: write(string filename) const{
	ofstream ofs(filename,ofstream::out);
	ofs<<"P6"<<endl<<width<<" "<<height<<" "<<255<<endl;
	ofs.write((const char*)data,width*height*3);
	ofs.close();
}

void image :: print(ostream &stream) const{
	stream << "IMAGE-\n";
	stream << "\twidth: " << width << endl;
	stream << "\theight: " << height << endl;
	stream << "\tbgcolor: ";
	bgcolor.print(stream);
}
