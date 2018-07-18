#pragma once

#include "vector3.h"
#include "color.h"
#include "camera.h"
#include "image.h"
#include "material.h"
#include "sphere.h"
#include "light.h"
#include "integrator.h"

#include "../tinyxml/tinyxml.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
using namespace std;

///Forward Declaration
class integrator;

class scene{
	private:
		string filename;
		/// Parse functions for different properties. 
	    string parse_parameter(TiXmlElement* element, string type);
	    int parse_int(TiXmlElement* element, string tag);
	    float parse_float(TiXmlElement* element, string tag);
	    float parse_float(string val);
		bool parse_bool(TiXmlElement* element, string tag);
	    float parse_angle(TiXmlElement* element, string tag);
	    color parse_color(TiXmlElement* element, string tag);
	    vector3 parse_vector3(TiXmlElement* element, string tag);

		/// Returns a pointed to a material called name from the material list.
	    material* find_material(string name, const list<material*> matlist);
	    
	    // Parse functions for different elements of scene file. 
	    bool parse_scenefile(void);
		camera* parse_camera(TiXmlElement* element);
	    int parse_objects(TiXmlElement* element, const list<material*>& materials);
	    object* parse_object_sphere(TiXmlElement* element, const list<material*>& materials);
	    int parse_materials(TiXmlElement* element);
	    material* parse_simplemat(TiXmlElement* element);
	    int parse_lights(TiXmlElement* element);
	    light* parse_pointlight(TiXmlElement* element);
	    image* parse_image(TiXmlElement* element);
	    integrator* parse_integrator(TiXmlElement* element);
	    integrator* parse_whitted_integrator(TiXmlElement *element);

	public:
		camera* cmr;
		image* img;
		list<material*> materials;
		list<object*> objects;
		list<light*> lights;
		integrator* intgrtr;
		int n_objects, n_materials, n_lights;

	    scene(string fname)
	    {
	    	filename = fname;
	    	parse_scenefile();
	    }

	    ~scene()
	    {
	        materials.clear();
	        objects.clear();
	        lights.clear();
	        delete img;
	    }
};