#include <iostream>
#include <scene.h>
#include <stdlib.h>
using namespace std;

color RayTrace(const scene* scn, ray camera_ray, int depth){
	list<object*>::const_iterator oit;
	hit_record hit;
	object* temp = NULL;
	for (oit=scn->objects.begin(); oit!=scn->objects.end(); oit++){
		if ((*oit)->intersect(hit, camera_ray)){
			camera_ray.max_t = hit.second;
			temp = *oit;
		}
	}
	
	color clr(0.0,0.0,0.0);
	if(temp){	
		list<light*>::const_iterator lit;
		vector3 normal = hit.first;
		vector3 point = camera_ray.pointAt(hit.second);
		for(lit=scn->lights.begin(); lit!=scn->lights.end(); lit++){
			bool direct = true;
			vector3 direction = (*lit)->get_position()-point;
			direction.unit_vector();
			ray shadow_ray(point,direction,0,10000);
			for (oit=scn->objects.begin(); oit!=scn->objects.end(); oit++){
				if ((*oit)->intersect(hit, shadow_ray)){
					if(*oit!=temp){
						direct = false;
						if((*oit)->get_material()->get_istransmit()){
							clr += (*oit)->get_material()->get_transmit()*(*lit)->get_clr()*(*lit)->get_ka();
						}
					}
				}	
			}
			if(direct){
				clr += (*lit)->get_clr()*(*lit)->get_ka();
			}
			clr += temp->get_material()->get_diffuse()*max((float)0.0,direction.dot(normal));
			vector3 reflect = normal*2.0*direction.dot(normal)-direction;
			clr += temp->get_material()->get_specular()*pow(max((float)0.0,camera_ray.get_direction().dot(reflect)),temp->get_material()->get_n());
				
		}
	}
	else clr = scn->img->get_bgcolor();
	clr.clamp();
	return clr;
}

void RenderPicture(const scene* scn){
	int w=scn->img->get_width();
  	int h=scn->img->get_height();
  	int n=16;
  	for(int i=0; i<w; i++){
  		for(int j=0; j<h; j++){
  			color c(0.0,0.0,0.0);
  			for(int k=0; k<n; k++){
  				ray camera_ray = scn->cmr->generate_ray(i+drand48(),j+drand48(),w,h);
  				c += RayTrace(scn,camera_ray,0);
  			}
  			c /= n;
  			scn->img->set_pixel(i,j,c);
  		}
  	}
}

int main(int argc, char **argv)
{
	string scene_filename(argv[1]);
  	scene scn(scene_filename);
  	RenderPicture(&scn);
  	scn.img->write(argv[2]);
	return 0;
}