#ifndef FINISH_H
#define FINISH_H

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

class FinishObj : public RayTracerObject {
  public:
    FinishObj();
    FinishObj(int id);
    ~FinishObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, FinishObj &fObj);    
    float ambient;
    float diffuse;
    float specular;
    float roughness;
    float reflection;
    float refraction;
    float ior;
};

#endif