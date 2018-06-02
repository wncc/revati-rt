#include "vector3.h"
#include "color.h"
#include "light.h"
#include "image.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
#include "../tinyxml/tinyxml.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

vector3 GetVector(TiXmlElement *element){
    string str = element->Attribute("vector3");
    istringstream buf(str);
    istream_iterator<std::string> beg(buf), end;
    vector<string> tokens(beg, end);
    return vector3(stof(tokens[0]),stof(tokens[1]),stof(tokens[2]));
}

color GetColor(TiXmlElement *element){
    string str = element->Attribute("color");
    istringstream buf(str);
    istream_iterator<std::string> beg(buf), end;
    vector<string> tokens(beg, end);
    return color(stof(tokens[0]),stof(tokens[1]),stof(tokens[2]));
}

double GetAngle(TiXmlElement *element){
    string str = element->Attribute("angle");
    return stof(str.substr(0,str.find(' ')));
}

double GetDouble(TiXmlElement *element){
	double d;
    element->QueryDoubleAttribute("double", &d);
    return d;
}

int GetInt(TiXmlElement *element){
	int d;
    element->QueryIntAttribute("int", &d);
    return d;
}

bool GetBool(TiXmlElement *element){
	const char* value = element->Attribute("bool");
	if(strcmp(value,"true")==0) return 1;
	else if(strcmp(value,"false")==0) return 0;
}

void LoadScene(const char *filename){
	TiXmlDocument doc(filename);
	if(!doc.LoadFile()){
        printf("Failed to load the file \"%s\"\n", filename);
        return;
    }

	TiXmlHandle docHandle(&doc);

    TiXmlElement *Camera = docHandle.FirstChild("rt-scene").FirstChild("camera").Element();
    if(!Camera){
        printf("No camera tag found.\n");
        return;
    }
    camera cam;
    TiXmlElement *child = Camera->FirstChildElement();
    while(child){
    	if      (strcmp(child->Value(),"lookat")==0) cam.lookat = GetVector(child);
        else if (strcmp(child->Value(),"eye")==0) cam.eye = GetVector(child);
        else if (strcmp(child->Value(),"up")==0) cam.up = GetVector(child);
        else if (strcmp(child->Value(),"fov")==0) cam.fov = GetAngle(child);
        else if (strcmp(child->Value(),"near")==0) cam.near = GetDouble(child);
        else if (strcmp(child->Value(),"far")==0) cam.far = GetDouble(child);
        child = child->NextSiblingElement();
    }
    cam.print();

    TiXmlElement *Image = Camera->NextSiblingElement();
    if(!Image){
        printf("No image tag found.\n");
        return;
    }
    image img;
    child = Image->FirstChildElement();
    while(child){
    	if      (strcmp(child->Value(),"width")==0) img.width = GetDouble(child);
        else if (strcmp(child->Value(),"height")==0) img.height = GetDouble(child);
        else if (strcmp(child->Value(),"bgcolor")==0) img.bgcolor = GetColor(child);
        child = child->NextSiblingElement();
    }
    img.print();

    TiXmlElement *Materials = Image->NextSiblingElement();
    if(!Materials){
        printf("No materials tag found.\n");
        return;
    }
    TiXmlElement *Simplemat = Materials->FirstChildElement();
    while(Simplemat){
	    material simplemat;
	    simplemat.id = Simplemat->Attribute("id");
	    child = Simplemat->FirstChildElement();
	    while(child){
	    	if 		(strcmp(child->Value(),"diffuse")==0) simplemat.diffuse = GetColor(child);
	        else if (strcmp(child->Value(),"specular")==0) simplemat.specular = GetColor(child);
	        else if (strcmp(child->Value(),"reflect")==0) simplemat.reflect = GetColor(child);
	        else if (strcmp(child->Value(),"transmit")==0) simplemat.transmit = GetColor(child);
	        else if (strcmp(child->Value(),"eta")==0) simplemat.eta = GetDouble(child);
	        else if (strcmp(child->Value(),"n")==0) simplemat.n = GetDouble(child);
	        else if (strcmp(child->Value(),"isreflect")==0) simplemat.isreflect = GetBool(child);
	        else if (strcmp(child->Value(),"istransmit")==0) simplemat.istransmit = GetBool(child);
	        child = child->NextSiblingElement();
	    }
	    simplemat.print();
	    Simplemat = Simplemat->NextSiblingElement();
	}

    TiXmlElement *Objects = Materials->NextSiblingElement();
    if(!Objects){
        printf("No objects tag found.\n");
        return;
    }
    TiXmlElement *Sphere = Objects->FirstChildElement();
    while(Sphere){
	    sphere sphr;
	    sphr.material = Sphere->Attribute("material");
	    child = Sphere->FirstChildElement();
	    while(child){
	    	if      (strcmp(child->Value(),"center")==0) sphr.center = GetVector(child);
	        else if (strcmp(child->Value(),"radius")==0) sphr.radius = GetDouble(child);
	        child = child->NextSiblingElement();
	    }
	    sphr.print();
	    Sphere = Sphere->NextSiblingElement();
	}

    TiXmlElement *Lights = Objects->NextSiblingElement();
    if(!Lights){
        printf("No lights tag found.\n");
        return;
    }
    TiXmlElement *Pointlight = Lights->FirstChildElement();
    while(Pointlight){
	    light plight;
	    child = Pointlight->FirstChildElement();
	    while(child){
	    	if      (strcmp(child->Value(),"position")==0) plight.position = GetVector(child);
	        else if (strcmp(child->Value(),"color")==0) plight.clr = GetColor(child);
	        else if (strcmp(child->Value(),"ka")==0) plight.ka = GetDouble(child);
	        child = child->NextSiblingElement();
	    }
	    plight.print();
	    Pointlight = Pointlight->NextSiblingElement();
	}

    TiXmlElement *Integrator = Lights->NextSiblingElement();
    if(!Integrator){
        printf("No integrator tag found.\n");
        return;
    }
    TiXmlElement *Whitted = Integrator->FirstChildElement();
    child = Whitted->FirstChildElement();
    int depth_of_recursion;
    if(strcmp(child->Value(),"depth-of-recursion")==0) depth_of_recursion = GetInt(child);
    printf("WHITTED-\n");
    printf("\tdepth-of-recursion: %d\n", depth_of_recursion);
}

int main(int argc, char const *argv[]){
	LoadScene("scenes/shadow.xml");
	return 0;
}