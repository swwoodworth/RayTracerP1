#ifndef SPHERE_H
#define SPHERE_H

#include "RayTracerObject.hpp"
#include "Geometry.hpp"
#include "PigmentObj.hpp"
#include "FinishObj.hpp"
#include "TranslateObj.hpp"
#include "ScaleObj.hpp"
#include "RotateObj.hpp"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

using namespace std;
using namespace glm;

class SphereObj : public Geometry {
  public:
    SphereObj();
    SphereObj(int id);
    ~SphereObj();
    void parse(ifstream &povFile);
    bool intersect(vec3 d, vec3 p_0, float* t);
    vec3 getNormal(vec3 intersect);
    vec3 getBBoxCorner1();
    vec3 getBBoxCorner2();
    friend ostream& operator<< (ostream &out, SphereObj &sphereObj);    
    vec3 location;
    double radius;
};

#endif