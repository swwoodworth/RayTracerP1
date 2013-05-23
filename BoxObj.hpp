#ifndef BOX_H
#define BOX_H

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

class BoxObj : public Geometry {
  public:
    BoxObj();
    BoxObj(int id);
    ~BoxObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, BoxObj &boxObj);
    bool intersect(vec3 d, vec3 p_0, float* t);
    vec3 getNormal(vec3 intersect); 
    vec3 getBBoxCorner1();
    vec3 getBBoxCorner2();
    vec3 corner1;
    vec3 corner2;
};

#endif