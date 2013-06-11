#ifndef GEOM_H
#define GEOM_H

#include "RayTracerObject.hpp"
#include "PigmentObj.hpp"
#include "FinishObj.hpp"
#include "TranslateObj.hpp"
#include "ScaleObj.hpp"
#include "RotateObj.hpp"
#include "Texture.hpp"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

using namespace std;
using namespace glm;

extern vector<Texture*> textures;

class Geometry : public RayTracerObject {
  public:
    Geometry();
    Geometry(int id);
    ~Geometry();
    virtual void parse(ifstream &povFile) {cout << "Parse is not implemented for this object" << endl;}; //base class parse function
    virtual bool intersect(vec3 d, vec3 p_0, float* t) {return false;};
    virtual vec3 getNormal(vec3 intersect) {return vec3(0.0,0.0,0.0);};
    virtual vec3 getBBoxCorner1() {return vec3(0.0,0.0,0.0);};
    virtual vec3 getBBoxCorner2() {return vec3(0.0,0.0,0.0);};
    void parseGeometry(ifstream &povFile);
    mat4 getTransformation();
    friend ostream& operator<< (ostream &out, Geometry &gObj) {out << "Not implemented";
                                                               return out;};    
    PigmentObj *pObj;
    FinishObj *fObj;
    TranslateObj *tObj;
    ScaleObj *sObj;
    RotateObj *rObj;
    vec3 center;
    mat4 m;
    mat4 m_i;
    bool perlin;
    bool perlinNormal;
    string texture;
    int pl;
};

#endif