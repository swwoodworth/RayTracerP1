#ifndef PLANE_H
#define PLANE_H

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

class PlaneObj : public RayTracerObject {
  public:
    PlaneObj();
    PlaneObj(int id);
    ~PlaneObj();
    void parse(ifstream &povFile);
    double intersect(vec3 d, vec3 p_0);
    friend ostream& operator<< (ostream &out, PlaneObj &planeObj);    
    vec3 normal;
    float distance;
    PigmentObj *pObj;
    FinishObj *fObj;
    TranslateObj *tObj;
    ScaleObj *sObj;
    RotateObj *rObj;
};

#endif