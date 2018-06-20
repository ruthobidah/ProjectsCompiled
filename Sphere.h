
#include "glm/vec3.hpp"
#include "Group.h"
#include "Object.h"
#include "Ray.h"
#include "Hit.h"
#include <vector>
#ifndef _SPHERE_H_
#define _SPHERE_H_

class Sphere: public Object
{
private:
  
public:
	glm::vec3 _center;
    	float _radius;
	int _materialIndex;
	Sphere(float r , glm::vec3 c , int m ):Object(), _radius(r), _center(c), _materialIndex(m){};
  	~Sphere( ){ };
  	float getRadius(){return _radius;}
  	glm::vec3 getCenter(){return _center;}
	int getMaterialIndex(){return _materialIndex;}
  
     Sphere & operator=(Sphere & s)
    {
  		_radius = s._radius; 
  		_center = s._center; 
		_materialIndex = s._materialIndex;
  		return *this;
    }


	bool intersect ( Ray &r, Hit &h, float &t ){  //r=radius //ray const
  
	    glm::vec3 tmp = r.getPoint( ) - _center;
	    float a = glm::dot(r.getDirection( ), r.getDirection( ));
	    float b = 2.0 * glm::dot(tmp, r.getDirection( ));
	    float c = glm::dot(tmp, tmp) - (_radius * _radius);
	    float discriminant = b * b - 4.0 * a * c;
	    if(discriminant < 0.0){
	      return false;
	    }else{
	      float e = std::sqrt(discriminant);
	      float denom = 2.0 * a;
	      t = (-b - e) / denom;
	      if(t > 0.000001){
	      	h.normal = normalize((tmp + t * r.getDirection()) / _radius);
	      	h.hitPoint = r.getPoint() + t * r.getDirection();
		return true;
	      }
	      t = (-b + e) / denom;
	      if(t > 0.000001){
	      	h.normal = (tmp + t * r.getDirection()) / _radius;
	      	h.hitPoint = r.getPoint() + t * r.getDirection();
		return true;
	      }
	    }
	    return false;
  }


};
#endif
