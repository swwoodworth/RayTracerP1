#ifndef TRANS_H
#define TRANS_H

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

class TranslateObj : public RayTracerObject {
  public:
    TranslateObj();
    TranslateObj(int id);
    ~TranslateObj();
    void parse(ifstream &povFile);
    mat4 getTranslate();
    friend ostream& operator<< (ostream &out, TranslateObj &tObj);    
    vec3 translation;
    mat4 transformation;
};

#endif