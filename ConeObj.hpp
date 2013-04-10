#ifndef CONE_H
#define CONE_H

#include "RayTracerObject.hpp"
#include "PigmentObj.hpp"
#include "FinishObj.hpp"
#include "TranslateObj.hpp"
#include "ScaleObj.hpp"
#include "RotateObj.hpp"

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

class ConeObj : public RayTracerObject {
  public:
    ConeObj();
    ConeObj(int id);
    ~ConeObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, ConeObj &coneObj);    
    vec3 end1;
    vec3 end2;
    double radius1;
    double radius2;
    PigmentObj *pObj;
    FinishObj *fObj;
    TranslateObj *tObj;
    ScaleObj *sObj;
    RotateObj *rObj;
};

#endif