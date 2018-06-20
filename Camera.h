/* Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: Camera.h 1961 2017-12-05 08:46:53Z mshafae $
 *
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <vector>
#include "glm/glm.hpp"

class Camera{
public:
	glm::vec3 _center;//_position;
 	glm::vec3 _direction;//_lookAt;
 	glm::vec3 _up;
 	float _fovY;
 
	Camera(){};
 	Camera(glm::vec3 c, glm::vec3 d, glm::vec3 myup): _center(c), _direction(d), _up(myup){};
 	Camera(glm::vec3 c, glm::vec3 d, glm::vec3 myup, float y): _center(c), _direction(d), _up(myup), _fovY(y) {};
 ~Camera( ){};

  Camera& operator=(Camera& c)
     {
  	_center = c._center;
  	_direction = c._direction;
  	_up = c._up;
  	_fovY = c._fovY;
  	return *this;
     }

};
#endif

