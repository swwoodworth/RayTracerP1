#ifndef SCALE_H
#define SCALE_H

#include "RayTracerObject.hpp"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

using namespace std;
using namespace glm;

class ScaleObj : public RayTracerObject {
  public:
    ScaleObj();
    ScaleObj(int id);
    ~ScaleObj();
    void parse(ifstream &povFile);
    mat4 getScale();
    friend ostream& operator<< (ostream &out, ScaleObj &sObj);    
    vec3 scale;
};

#endif