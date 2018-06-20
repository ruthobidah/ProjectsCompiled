/* Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: Ray.h 1961 2017-12-05 08:46:53Z mshafae $
 *
 */

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"
#include "glm/gtx/string_cast.hpp"

#ifndef _RAY_H_
#define _RAY_H_

class Ray{
	glm::vec3 _p;
	glm::vec3 _d;
	glm::vec3 _ray = _p + _d;
	int _i; //pixel coord
	int _j; //pixel coord
public:

	Ray(glm::vec3 p, glm::vec3 d, int i, int j): _p(p), _d(d), _i(i), _j(j){
		// d should be a unit length vector plus or minus epsilon
		//assert(glm::length2(d) < 1.000001);
		assert(glm::epsilonEqual(glm::length(d), 1.0f, 0.00001f));
	};//initalize data members without going into constructor

/* //construct this one from previoius - complier cant tell the difference 
	Ray(glm::vec3 p0, glm::vec3 p1): _p(p1){
		_d = (p0 - p1);
		_d = _d / length(_d);
	}
*/
	~Ray( ){};

	glm::vec3 getPoint()
	{
		return _p;
	}

	glm::vec3 getDirection()
	{
		return _d;
	}

	glm::vec3 getRay()
	{
		return _ray;
	}

	int getX()
	{
		return _i;
	}

	int getY()
	{
		return _j;
	}

	std::ostream& write(std::ostream &out) const {
		out << "Ray(p = " << glm::to_string(_p) << ", d = " << glm::to_string(_d) << ", i = " << _i << ", j = " << _j << std::endl;
		return out;
	}

};

#endif
