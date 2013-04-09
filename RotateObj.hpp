#ifndef ROTATE_H
#define ROTATE_H

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

class RotateObj : public RayTracerObject {
  public:
    RotateObj();
    RotateObj(int id);
    ~RotateObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, RotateObj &rObj);    
    vec3 rotation;
};

#endif