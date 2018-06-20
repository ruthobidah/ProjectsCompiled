/* Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: Group.h 1961 2017-12-05 08:46:53Z mshafae $
 *
 */

#ifndef _GROUP_H_
#define _GROUP_H_

#include <vector>
#include "Ray.h"
#include "Object.h"
#include "glm/glm.hpp"
using namespace std;

class Group{
public:
	float _numObjects;
	float _materialIndex;
 	vector<Object*> myObjects; //vector container of object pointers

	Group(){};
	Group( float n, float m, vector<Object*> o): _numObjects(n),
	 _materialIndex(m), myObjects(o) {};
	~Group( ){};

  Group& operator=(Group& g)  //overload operator
    {
  	
  	_numObjects = g._numObjects;
  	_materialIndex = g._materialIndex;
  	myObjects = g.myObjects;
  	return *this;
    }
};

#endif
