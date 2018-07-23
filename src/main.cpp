#include <iostream>
#include <scene.h>
#include <stdlib.h>
using namespace std;

color RayTrace(const scene* scn, ray camera_ray, int depth){
	list<object*>::const_iterator oit;
	double t = -1;
	object* temp = NULL;

	// Finds the closest intersection with objects if any
	for (oit=scn->objects.begin(); oit!=scn->objects.end(); oit++){
		if ((*oit)->intersect(t, camera_ray)){
			camera_ray.max_t = t;
			temp = *oit;
		}
	}
	
	color C;
	double t1 = -1;
	if(temp){	
		vector3 point = camera_ray.pointAt(t);
		vector3 normal = temp->get_normal(point);
		vector3 view  = (camera_ray.get_direction()).unit();
		double far = scn->cmr->get_far();
		double near = scn->cmr->get_near();
		list<light*>::const_iterator lit;

		// For each light compute the shadow ray (from intersection point to light)
		for(lit=scn->lights.begin(); lit!=scn->lights.end(); lit++){
			color light = (*lit)->get_clr()*(*lit)->get_ka();
			vector3 direction = ((*lit)->get_position()-point).unit();
			ray shadow_ray(point,direction,near,far);

			// For each object check if any object interects the shadow ray
			for (oit=scn->objects.begin(); oit!=scn->objects.end(); oit++){
				if ((*oit)->intersect(t1, shadow_ray)){
					if(*oit!=temp){
						// Compute the transmitted light through the object
						light *= (*oit)->get_material()->get_transmit();
					}
				}	
			}

			// Computed the color because of diffused reflection
			double diffusion = direction.dot(normal);
			if(diffusion>0)
				C += light*temp->get_material()->get_diffuse()*diffusion;

			// Computed the color because of specular reflection
			vector3 reflected = (direction-normal*2.0*direction.dot(normal)).unit();
			double specular = view.dot(reflected);
			if(specular>0)
				C += light*temp->get_material()->get_specular()*pow(specular,temp->get_material()->get_n());	
		}


		// if(scn->intgrtr->get_depth() > depth){
		// 	// Generate the reflected camera ray from intersection point
		// 	ray reflected_ray(point, (view-normal*2.0*view.dot(normal)).unit(),near,far);
		// 	// Compute the color due to reflection recursively
		// 	C += RayTrace(scn, reflected_ray, depth + 1) * temp->get_material()->get_reflect();

		// 	double cosi = view.dot(normal); 
  //   		double eta = temp->get_material()->get_eta(); 
  //   		if (cosi < 0) {
  //   			eta = 1/eta; 
  //   			cosi = -cosi; 
  //   		} else {
  //   			normal = -normal; 
  //   		} 
  //   		double k = 1 - eta * eta * (1 - cosi * cosi); 
  //   		vector3 refracted_d(0,0,0); 
  //   		if (k>0){
  //   			refracted_d = view * eta + normal * (eta * cosi - sqrtf(k));
  //   		}
		// 	ray refracted_ray(point, refracted_d,0,10000);
		// 	C += RayTrace(scn, refracted_ray, depth + 1);
		// }
	}
	else {
		// In case of no intersection the color will be the background color
		C = scn->img->get_bgcolor();
	}
	C.clamp();
	return C;
}

void RenderPicture(const scene* scn){
	int w=scn->img->get_width();
  	int h=scn->img->get_height();
  	int n=4;

  	// For each pixel(i,j) on the screen
  	for(int i=0; i<w; i++){
  		for(int j=0; j<h; j++){
  			color c(0.0,0.0,0.0);
  			for(int k=0; k<n; k++){
  				// Generate a ray from the camera eye through the point on the view plane corresponding to this pixel
  				ray camera_ray = scn->cmr->generate_ray(i+drand48(),j+drand48(),w,h);
  				c += RayTrace(scn,camera_ray,0);
  			}
  			c /= n;
  			// Set the pixel color value returned by RayTrace()
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