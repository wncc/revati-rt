#include <scene.h>
using namespace std;

string scene::parse_parameter(TiXmlElement* element, string type){
	const char *value = element->Attribute(type.c_str());
	if (!value)
		value = element->Attribute("double");
	if (!value)
		throw invalid_argument("Scene file parameter expected type");
	return string(value);
}

material* scene::find_material(string name, const list<material*> matlist){
	for (list<material*>::const_iterator it = matlist.begin(); it != matlist.end(); it++){
		if((*it)->get_id() == name) return (*it);
	}
	throw invalid_argument("Material from object not found in scene file.");
}

int scene::parse_int(TiXmlElement* element, string tag){
	TiXmlElement* subelement = element->FirstChildElement(tag.c_str());
	istringstream stream(string(subelement->Attribute("int")));
	int val;
	stream >> val;
	return val;
}

double scene::parse_double(TiXmlElement* element, string tag){
	return parse_double(parse_parameter(element->FirstChildElement(tag.c_str()), "double"));
}

double scene::parse_double(string value){
	istringstream stream(value);
	double val;
	stream >> val;
	return val;
}

bool scene::parse_bool(TiXmlElement* element, string tag){
	TiXmlElement* subelement = element->FirstChildElement(tag.c_str());
	istringstream stream(string(subelement->Attribute("bool")));
	bool val;
	stream >> val;
	return val;
}

double scene::parse_angle(TiXmlElement* element, string tag){
	TiXmlElement* subelement = element->FirstChildElement(tag.c_str());
	istringstream stream(string(subelement->Attribute("angle")));
	double val;
	string unit;
	stream >> val >> unit;
	if(unit == "deg")
		val *= M_PI / 180.0;
	else 
		throw invalid_argument("Angle must have unit \"deg\"");
	return val;
}

color scene::parse_color(TiXmlElement* element, string tag){
	TiXmlElement* subelement = element->FirstChildElement(tag.c_str());
	istringstream stream(string(subelement->Attribute("color")));
	double x, y, z;
	stream >> x >> y >> z;
	return color(x,y,z);
}

vector3 scene::parse_vector3(TiXmlElement* element, string tag){
	TiXmlElement* subelement = element->FirstChildElement(tag.c_str());
	istringstream stream(string(subelement->Attribute("vector3")));
	double x, y, z;
	stream >> x >> y >> z;
	return vector3(x,y,z);
}

bool scene::parse_scenefile(void){
	TiXmlDocument doc(filename.c_str());
	if (!doc.LoadFile())
		throw runtime_error("Cannot read scene file.");

	TiXmlElement* doc_root = doc.RootElement();
	if (!doc_root)
		throw runtime_error("Scene file is not a valid scene description");

	cmr = parse_camera(doc_root);
	cmr->print(cerr);

	img = parse_image(doc_root);
	img->print(cerr);

	intgrtr = parse_integrator(doc_root);

	n_materials = parse_materials(doc_root);
	for (list<material*>::iterator it=materials.begin(); it!=materials.end(); it++){
		(*it)->print(cerr);
	}

	n_objects = parse_objects(doc_root, materials);
	for (list<object*>::iterator it=objects.begin(); it!=objects.end(); it++){
		(*it)->print(cerr);
	}

	n_lights = parse_lights(doc_root);
	for (list<light*>::iterator it=lights.begin(); it!=lights.end(); it++){
		(*it)->print(cerr);
	}
	return true;
}

camera* scene::parse_camera(TiXmlElement* element){
	TiXmlElement* element_camera = element->FirstChildElement("camera");
	if (!element_camera)
		throw runtime_error("Scene file does not contain a camera.");

	return (new camera(
					parse_vector3(element_camera, "lookat"),
					parse_vector3(element_camera, "eye"),
					parse_vector3(element_camera, "up"),
					parse_angle(element_camera, "fov"),
					parse_double(element_camera, "near"),
					parse_double(element_camera, "far")
				));
}

image* scene::parse_image(TiXmlElement* element){
	TiXmlElement* element_image = element->FirstChildElement("image");
	if (!element_image)
		throw runtime_error("No image found in scene file.");
	return new image(	
					parse_double(element_image, "width"),
					parse_double(element_image, "height"),
					parse_color(element_image, "bgcolor"));
}

int scene::parse_materials(TiXmlElement* element){
	materials.clear();
	TiXmlElement* element_materials = element->FirstChildElement("materials");
	if (!element_materials)
		throw runtime_error("No materials found in scene file.");

	int n_materials=1;
	TiXmlElement* child = element_materials->FirstChildElement();
	while (child) 
	{
		materials.push_back(parse_simplemat(child));
		child = child->NextSiblingElement();
		n_materials++;
	}
	return n_materials;
}

material* scene::parse_simplemat(TiXmlElement* element){
	return (material*)(new material(
			parse_parameter(element, "id"),
			parse_color(element, "diffuse"),
			parse_color(element, "specular"),
			parse_color(element, "reflect"),
			parse_color(element, "transmit"),
			parse_double(element, "eta"),
			parse_double(element, "n"),
			parse_bool(element, "isreflect"),
			parse_bool(element, "istransmit")));
}

int scene::parse_objects(TiXmlElement* element, const list<material*>& matlist){
	objects.clear();

	TiXmlElement* element_objects = element->FirstChildElement("objects");
	if (!element_objects)
		throw runtime_error("No objects found in scene file.");

	int n_objects=1;
	TiXmlElement* child = element_objects->FirstChildElement();
	while (child)
	{
		string name(child->Value());
		if(name=="sphere"){
			objects.push_back(parse_object_sphere(child, matlist));
		} else if(name=="cone"){
			objects.push_back(parse_object_cone(child, matlist));
		} else if(name=="cylinder"){
			objects.push_back(parse_object_cylinder(child, matlist));
		} else{
			throw invalid_argument("Invalid object in scene file.");
		}
		child = child->NextSiblingElement();
		n_objects++;
	}

	if (objects.empty())
		throw invalid_argument("Could not parse object.");
	else 
		return n_objects;
}

object* scene::parse_object_sphere(TiXmlElement* element, const list<material*>& matlist){
	material* m = find_material(parse_parameter(element, "material"),	matlist);
	return (object*)(new sphere(m,
								parse_vector3(element,  "center"),
								parse_double(element, "radius")));
}

object* scene::parse_object_cone(TiXmlElement* element, const list<material*>& matlist){
	material* m = find_material(parse_parameter(element, "material"),	matlist);
	return (object*)(new cone(m,
								parse_vector3(element,  "center"),
								parse_double(element, "radius"),
								parse_double(element, "height")));
}

object* scene::parse_object_cylinder(TiXmlElement* element, const list<material*>& matlist){
	material* m = find_material(parse_parameter(element, "material"),	matlist);
	return (object*)(new cylinder(m,
								parse_vector3(element,  "center"),
								parse_double(element, "radius"),
								parse_double(element, "height")));
}

int scene::parse_lights(TiXmlElement* element){
	lights.clear();

	TiXmlElement* element_lit = element->FirstChildElement("lights");
	if (!element_lit)
		throw runtime_error("No lights found in scene file.");

	int n_lights=1;
	TiXmlElement* child = element_lit->FirstChildElement();
	while (child) 
	{
		string name(child->Value());

		if (name == "pointlight")
			lights.push_back(parse_pointlight(child));
		else
			throw invalid_argument("Invalid light in scene file.");
		
		child = child->NextSiblingElement();
		n_lights++;
	}
	return n_lights;
}

light* scene::parse_pointlight(TiXmlElement* element){
	return (light*)(new light(
			parse_vector3(element, "position"),
			parse_color(element, "color"),
			parse_double(element, "ka")));
}

integrator* scene::parse_integrator(TiXmlElement* element){
	TiXmlElement* element_intg = element->FirstChildElement("integrator");
	if (!element_intg)
		throw runtime_error("Scene file does not contain an integrator.");

	TiXmlElement* child = element_intg->FirstChildElement();
	string name(child->Value());
	if (name == "whitted"){
		return parse_whitted_integrator(child);
	}
	else
		throw invalid_argument("Invalid integrator in scene file.");		
}

integrator* scene::parse_whitted_integrator(TiXmlElement *element){
	return (integrator*)(new whitted_integrator(
								parse_int(element, "depth-of-recursion")));
}