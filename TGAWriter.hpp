#ifndef TGAW_H
#define TGAW_H

#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

#include "Pixel.hpp"

using namespace std;
using namespace glm;

extern string fileName;

class TGAWriter {
   public:
      Pixel *pixels;
      int screenWidth;
      int screenHeight;
      double max;
  
      TGAWriter(int width, int height); //default constructor
      ~TGAWriter(); //destructor
      void colorPixel(int pixel, vec3 color);
      void writeTGA(bool scale);
};

#endif