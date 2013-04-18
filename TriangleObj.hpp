#ifndef TRI_H
#define TRI_H

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

class TriangleObj : public Geometry {
  public:
    TriangleObj();
    TriangleObj(int id);
    ~TriangleObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, TriangleObj &triObj);    
    vec3 corner1;
    vec3 corner2;
    vec3 corner3;
};

#endif