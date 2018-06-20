/* Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: Material.h 1961 2017-12-05 08:46:53Z mshafae $
 *
 */
#include "glm/vec3.hpp"
#include "RGBcolor.h"
#include <vector>
using namespace std;

#ifndef _PHONG_MATERIAL_H_
#define _PHONG_MATERIAL_H_

class Material{
public:
	vector<RGBcolor*> myRGBcolors;       //container of RGBcolors
	
	Material(){};
	Material( vector<RGBcolor*> c): myRGBcolors(c){};
	~Material(){};


	Material& operator=(Material& m)
  	  {
  	
  		myRGBcolors = m.myRGBcolors;
  		return *this;
  	  }
};
#endif
