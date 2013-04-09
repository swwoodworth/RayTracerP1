#ifndef PIGMENT_H
#define PIGMENT_H

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

class PigmentObj : public RayTracerObject {
  public:
    PigmentObj();
    PigmentObj(int id);
    ~PigmentObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, PigmentObj &pObj);    
    vec4 pigment;
};

#endif