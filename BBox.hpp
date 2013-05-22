#ifndef BBOX_H
#define BBOX_H

#include "RayTracerObject.hpp"
#include "Geometry.hpp"
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

class BBox : public Geometry {
  public:
    BBox();
    BBox(Geometry *g);
    BBox(BBox *l, BBox *r);
    ~BBox();
    friend ostream& operator<< (ostream &out, BBox &bBox);
    bool intersect(vec3 d, vec3 p_0, float* t);
    vec3 getNormal(vec3 intersect); 
    void buildBB();
    void transformBB();
    
    vec3 corner1;
    vec3 corner2;
    vec3 c[8];
    Geometry *geometry;
    BBox *left;
    BBox *right;
};

#endif