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

using namespace std;
using namespace glm;

struct Pixel {
   int r, g, b;
};

class TGAWriter {
  public:
   TGAWriter(); //default constructor
   ~TGAWriter(); //destructor
   void writeTGA(Pixel *pixels, int screenHeight, int screenWidth);
};

#endif