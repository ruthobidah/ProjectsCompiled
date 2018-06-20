/*
 * Copyright (c) 2005-2013 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id: Image.h 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include <FreeImagePlus.h>

/*#undef FREEIMAGE_COLORORDER
#define FREEIMAGE_COLORORDER FREEIMAGE_COLORORDER_BGR*/

#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef unsigned char channel;  

class Pixel {
public:
  Pixel( ) { r = 0; g = 0; b = 0; };
  Pixel( channel _r, channel _g, channel _b ) { r = _r; g = _g; b = _b; };
  void write( std::ostream &out ) const{
    out << "[" << r << ", " << g << ", " << b <<", " << "]";
  };
  channel r;
  channel g;
  channel b;
};

std::ostream& operator <<( std::ostream &out, const Pixel &p );

//typedef RGBQUAD Pixel;

class Image{
public:
  Image( const std::string& filename, uint width, uint height, uint bpp) : _filename(filename), _width(width), _height(height){
    _image = fipImage(FIT_BITMAP, width, height, bpp);
  }
  virtual ~Image( ){ }
  uint width( ) const{
    uint w = _image.getWidth( );
    assert(w == _width);
    return _width;
  }
  std::string filename( ) const{
    return _filename;
  }
  const char* c_str_filename( ) const{
    return _filename.c_str( );
  }
  uint height( ) const{
    uint h = _image.getHeight( );
    assert(h == _height);
    return _height;
  }
  uint scanWidthInBytes( ) const{
    return _image.getLine( );
  }
  bool isValid( ) const{
    return _image.isValid( );
  }
  uint imageSizeInBytes( ) const{
    return _image.getImageSize( );
  }
  uint scanWidthInPixels(size_t type) const{
    //std::cerr << "getline " << _image.getLine( ) << std::endl;
    //std::cerr << "size " << type << std::endl;
    return _image.getLine( ) / type;
  }
  BYTE* scanLine(uint i, size_t type) const{
  //RGBQUAD* scanLine(uint i) const{
    assert(i < _image.getLine( ) / type);
    assert(i < _height);
    return _image.getScanLine(i);
  }
  void fill(BYTE r, BYTE g, BYTE b, BYTE a, size_t type){
    /*RGBQUAD c;
    c.rgbRed = r;
    c.rgbGreen = g;
    c.rgbBlue = b;
    c.rgbReserved = a;*/
    for(unsigned int i = 0; i < height( ); i++){
      RGBQUAD* sl = (RGBQUAD*)scanLine(i, type);
      for(unsigned int j = 0; j < width( ); j++){
        sl[j].rgbRed = r;
        sl[j].rgbGreen = g;
        sl[j].rgbBlue = b;
        sl[j].rgbReserved = a;
      }
    }
  }
  
  void grayFill(BYTE g, size_t type){
    fill(g, g, g, 255, type);
  }
  
  void setPixel(uint x, uint y, BYTE r, BYTE g, BYTE b, BYTE a){
    RGBQUAD c;
    c.rgbRed = r;
    c.rgbGreen = g;
    c.rgbBlue = b;
    c.rgbReserved = a;
    _image.setPixelColor(x, y, &c);
  }
  
  /*void setPixel(uint x, uint y, const RGBAColor& c){
    RGBQUAD q;
    c.copyToRGBQuad(q);
    setPixel(x, y, c.redByte( ), c.greenByte( ), c.blueByte( ), c.alphaByte( ));
  }*/
  
  void setGrayPixelF(uint x, uint y, float g){
    g = std::max(std::min(g, 1.0f), 0.0f);
    double val = 255.0 * g;
    BYTE _g = static_cast<BYTE>(std::round(val));
    setPixel(x, y, _g, _g, _g, 255);
  }

  void setGrayPixel(uint x, uint y, BYTE g){
    setPixel(x, y, g, g, g, 255);
  }
  
  /*void setGrayPixel(uint x, uint y, float g){
    assert(g >= 0.0f && g <= 1.0f);
    BYTE _g = static_cast<BYTE>(std::floor(255 * g));
    setPixel(x, y, _g, _g, _g, 255);
  }*/
  
  bool getPixel(uint x, uint y, RGBQUAD* c){
    return _image.getPixelColor(x, y, c);
  }
  
  bool save(int flags){
    bool rv = _image.save(_filename.c_str( ), flags);
    assert(rv == true);
    return rv;
  }
private:
  std::string _filename;
  uint _width;
  uint _height;
  fipImage _image;
};

class PNGImage: public Image{
public:
  PNGImage( const std::string& filename, uint width, uint height ) : 
    Image(filename, width, height, 32){ }
  ~PNGImage( ){ }

  uint scanWidthInPixels( ) const{
    return Image::scanWidthInPixels(sizeof(RGBQUAD));
  }
  
  RGBQUAD* scanLine(uint i) const{
    return (RGBQUAD*)Image::scanLine(i, sizeof(RGBQUAD));
  }
  
  void fill(BYTE r, BYTE g, BYTE b, BYTE a){
    Image::fill(r, g, b, a, sizeof(RGBQUAD));
  }

  void grayFill(BYTE g){
    Image::grayFill(g, sizeof(RGBQUAD));
  }
  
  virtual bool save(uint compression = 3){
    int flags;
    if(compression == 0){
      flags = PNG_Z_NO_COMPRESSION;
    }else if(compression == 1){
      flags = PNG_Z_BEST_COMPRESSION;
    }else{
      flags = PNG_DEFAULT;
    }
    return Image::save(flags);
  }
};

class JPEGImage: public Image{
public:
  JPEGImage( const std::string& filename, uint width, uint height ) : 
    Image(filename, width, height, 24){ }
  ~JPEGImage( ){ }

  uint scanWidthInPixels( ) const{
    return Image::scanWidthInPixels(sizeof(RGBQUAD));
  }

  RGBQUAD* scanLine(uint i) const{
    return (RGBQUAD*)Image::scanLine(i, sizeof(RGBQUAD));
  }
  
  void fill(BYTE r, BYTE g, BYTE b){
    Image::fill(r, g, b, 255, sizeof(RGBQUAD));
  }
  
  void grayFill(BYTE g, size_t type){
    Image::grayFill(g, sizeof(RGBQUAD));
  }
  
  virtual bool save(uint compression = 75){
    assert(compression <= 100);
    bool val = Image::save(JPEG_PROGRESSIVE | JPEG_BASELINE | compression);
    assert( val == true);
    return val;
  }
};

/*
class EXRImage{
public:
  Imagef( const std::string& filename, uint width, uint height ) : _filename(filename), _width(width), _height(height){
    _image = fipImage(FIT_RGBAF, width, height, 128);
  }
  ~Imagef( ){ }
  uint width( ) const{
    uint w = _image.getWidth( );
    assert(w == _width);
    return _width;
  }
  uint height( ) const{
    uint h = _image.getHeight( );
    assert(h == _height);
    return _height;
  }
  uint scanWidthInBytes( ) const{
    return _image.getLine( );
  }
  bool isValid( ) const{
    return _image.isValid( );
  }
  uint imageSizeInBytes( ) const{
    return _image.getImageSize( );
  }
  uint scanWidthInPixels( ) const{
    return _image.getLine( ) / sizeof(float) * 4;
  }
  float* scanLine(uint i) const{
    assert(i < _image.getLine( ) / (sizeof(float) * 4));
    assert(i < _height);
    return (float*)_image.getScanLine(i);
  }
  void setPixel(uint x, uint y, float r, float g, float b, float a){
    float *c;
    float *sl = scanLine(y);
    c = sl + (y*sizeof(float));
    //c[FI_RGBA_RED] = r;
    //c[FI_RGBA_GREEN] = g;
    //c[FI_RGBA_BLUE] = b;
    //c[FI_RGBA_ALPHA] = a;
    c[0] = r;
    c[1] = g;
    c[2] = b;
    c[3] = a;

  }
  bool convert( ){
    return _image.convertTo32Bits( );
  }
  bool save( ){
    return _image.save(_filename.c_str( ), EXR_DEFAULT);
  }
private:
  std::string _filename;
  uint _width;
  uint _height;
  fipImage _image;
};
*/
#endif
