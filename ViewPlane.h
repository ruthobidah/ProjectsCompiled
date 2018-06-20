/* Bijan Hamidi & Ruth Obidah
 * bhamidi@csu.fullerton.edu, ruthobidah@csu.fullerton.edu
 * CS 599 Independent Study
 * December 2017
 *
 * $Id: Camera.h 1961 2017-12-05 08:46:53Z mshafae $
 *
 */

#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_

#include <vector>
#include "glm/glm.hpp"

class ViewPlane{
public:

 	int _width, _height;
  float _pixelSize;
  int _sampleCount; //number of  color samples per pixel

	ViewPlane(){};
 	ViewPlane(int w, int h, float p, int c ): _width(w), _height(h), _pixelSize(p), _sampleCount(c) {}
 	/*center = mycenter; 
 	direction = mydirection;
 	up = myup;
 	width = w;
 	height = h; };*/
 ~ViewPlane( ){};

  ViewPlane& operator=(ViewPlane& v)
     {
  	_width = v._width;
  	_height = v._height;
	  _pixelSize = v._pixelSize;
    _sampleCount = v._sampleCount;
  	return *this;
     }
  float pixelWidth( ) const {
    return _width / _pixelSize;
  }

  float pixelHeight( ) const {
    return _height / _pixelSize;
  }

};

#endif
