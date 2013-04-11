#ifndef RAYT_H
#define RAYT_H

#include "TGAWriter.hpp"

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


class RayTracer {
  public:
   RayTracer(); //default constructor
   ~RayTracer(); //destructor
   void trace(int screenWidth, int screenHeight);
};

#endif