/*Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
*/


#include "glm/vec3.hpp"
#include "RGBcolor.h"
#include <vector>
using namespace std;

#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "glm/vec3.hpp"

class Lights{
	public:
	vector<diffuseColor*> myDcolors;
	vector<ambientColor*> myAcolors;
	vector<SpecularColor*> myScolors;
	glm::vec3 _position;
	float _linearAttn;
	float _quadraticAttn;
	//RGBcolor( );
	Lights( glm::vec3 p, vector<diffuseColor*> d, vector<ambientColor*> a, vector<SpecularColor*> s, float ln, float q ):
	 _position(p), myAcolors(a),myDcolors(d), myScolors(s), _linearAttn(ln), _quadraticAttn(q) {};
	~Lights( );

	glm::vec3 getposition() {return _position;}

	Lights& operator=(Lights& l)
  	  {
  		_position = l._position;
  		myAcolors = l.myAcolors;
		myDcolors = l.myDcolors;
		myScolors = l.myScolors;
		_linearAttn = l._linearAttn;
		_quadraticAttn = l._quadraticAttn;
  		return *this;
  	  }

};

#endif
