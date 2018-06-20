// To build
//    clang++ -std=c++11 -I ~/github/TitanOpenGLKit/TitanOpenGLKit_osx/include/ -L ~/github/TitanOpenGLKit/TitanOpenGLKit_osx/lib/ demo_image.cpp  -lfreeimageplus
//
#include <iostream>
#include "Image.h"

using namespace std;

int main(void){
  static const unsigned int d = 500;

  PNGImage the_image("red.png", d, d);

  for(int i = 0; i < d; i++){
    for(int j = 0; j < d; j++){
      the_image.setPixel(i, j, 255, 0, 0, 255);
    }
  }

  the_image.save( );

  the_image = PNGImage("speckled.png", d, d);
  for(int i = 0; i < d; i++){
    for(int j = 0; j < d; j++){
      if( i % 2 == 0 && j % 2 == 0 ){
        the_image.setPixel(i, j, 0, 255, 0, 255);
      }else{
        the_image.setPixel(i, j, 255, 0, 0, 255);
      }
    }
  }

  the_image.save( );
  
  return 0;
}