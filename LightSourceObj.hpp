#ifndef LIGHT_H
#define LIGHT_H

#include "RayTracerObject.hpp"

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

class LightSourceObj : public RayTracerObject {
  public:
    LightSourceObj();
    LightSourceObj(int id);
    ~LightSourceObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, LightSourceObj &lsObj);    
    vec3 location;
    vec3 color;
};

#endif