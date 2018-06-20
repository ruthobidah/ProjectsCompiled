/*Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
*/

#ifndef _PHONGMATERIAL_H_
#define _PHONGMATERIAL_H_

#include "glm/vec3.hpp"

class PhongMaterial{
	public:
	glm::vec4 _ambientColor;
	glm::vec4 _diffuseColor;
	glm::vec4 _specularColor;
	int _shininess;
	//RGBcolor( );
	RGBcolor( glm::vec4 a, glm::vec4 d, glm::vec4 s, int sh): _ambientColor(a), _diffuseColor(d),
	 _specularColor(s), _shininess(sh) {};
	~PhongMaterial( );

	glm::vec4 getdiffuseColor() {return _diffuseColor;}
	glm::vec4 getambientColor() {return _ambientColor;}
	glm::vec4 getspecularColor() {return _specularColor;}
	int getShininess(){return _shininess;}

	RGBcolor & operator=(RGBcolor & r)
    	    {
  		_ambientColor = r._ambientColor;
		_diffuseColor = r._diffuseColor;
		_specularColor = r._specularColor;
		_shininess = r._shininess;
  		return *this;
    	    }

};

#endif
