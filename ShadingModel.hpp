#ifndef SHADE_H
#define SHADE_H

#include "CameraObj.hpp"
#include "LightSourceObj.hpp"

#include "SphereObj.hpp"
#include "BoxObj.hpp"
#include "ConeObj.hpp"
#include "PlaneObj.hpp"
#include "TriangleObj.hpp"

#include "RayTracerObject.hpp"
#include "Geometry.hpp"
#include "PigmentObj.hpp"
#include "FinishObj.hpp"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

#define PI 3.14159265359

extern vector<CameraObj*> cameras;
extern vector<LightSourceObj*> lights;
   
extern vector<SphereObj*> spheres;
extern vector<BoxObj*> boxes;
extern vector<ConeObj*> cones;
extern vector<PlaneObj*> planes;
extern vector<TriangleObj*> triangles;

extern vector<Geometry*> geometry;
extern vector<Texture*> textures;


using namespace std;
using namespace glm;

class ShadingModel {
  public:
    ShadingModel();
    ~ShadingModel();
    vec3 phong(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient);
    vec3 gaussian(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient);
    vec4 getPigment(Geometry *geom, vec3 intersect, vec3 norm);

};

#endif