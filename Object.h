/* Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: 3DObject.h 1961 2017-12-05 08:46:53Z mshafae $
 *
 */

#ifndef _OBJECT_
#define _OBJECT_
#include "glm/glm.hpp"
#include "Ray.h"
#include "Hit.h"


class Object                   //virtual object class for polymorphism
{

	public:
		
		Object(){};
		virtual ~Object(){};
                              //make subclass for circles and put 3dobjects in groups
                             //All objects have own intersect implementation, virtual function allows one call
	virtual bool intersect(Ray &r, Hit &h, float &t) = 0; // all intersects take a ray and hit object
	virtual int getMaterialIndex() = 0;
	
    Object& operator=(Object& o)
      {
  	//_s = o._s; 
  	return *this;
      }





};

#endif
