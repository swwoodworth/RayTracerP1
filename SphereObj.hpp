#ifndef SPHERE_H
#define SPHERE_H

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

class SphereObj : public RayTracerObject {
  public:
    SphereObj();
    SphereObj(int id);
    ~SphereObj();
    void parse(ifstream &povFile);
    double intersect(vec3 d, vec3 p_0);
    friend ostream& operator<< (ostream &out, SphereObj &sphereObj);    
    vec3 location;
    double radius;
    PigmentObj *pObj;
    FinishObj *fObj;
    TranslateObj *tObj;
    ScaleObj *sObj;
    RotateObj *rObj;
};

#endif