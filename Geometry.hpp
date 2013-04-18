#ifndef GEOM_H
#define GEOM_H

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

class Geometry : public RayTracerObject {
  public:
    Geometry();
    Geometry(int id);
    ~Geometry();
    virtual void parse(ifstream &povFile) {cout << "Parse is not implemented for this object" << endl;}; //base class parse function
    virtual double intersect(vec3 d, vec3 p_0) {return -1.0;};
    friend ostream& operator<< (ostream &out, Geometry &gObj) {out << "Not implemented";
                                                               return out;};    
    PigmentObj *pObj;
    FinishObj *fObj;
    TranslateObj *tObj;
    ScaleObj *sObj;
    RotateObj *rObj;
};

#endif