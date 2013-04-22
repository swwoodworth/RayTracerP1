#ifndef RAYT_H
#define RAYT_H

#include "TGAWriter.hpp"

#include "CameraObj.hpp"
#include "LightSourceObj.hpp"

#include "SphereObj.hpp"
#include "BoxObj.hpp"
#include "ConeObj.hpp"
#include "PlaneObj.hpp"
#include "TriangleObj.hpp"
#include "RayTracer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

using namespace std;
using namespace glm;

extern vector<CameraObj*> cameras;
extern vector<LightSourceObj*> lights;
   
extern vector<SphereObj*> spheres;
extern vector<BoxObj*> boxes;
extern vector<ConeObj*> cones;
extern vector<PlaneObj*> planes;
extern vector<TriangleObj*> triangles;

extern vector<Geometry*> geometry;


extern int screenWidth;
extern int screenHeight;

class RayTracer {
  public:
   RayTracer(); //default constructor
   ~RayTracer(); //destructor
   void genRays();
   vec3 raytrace(vec3 d, vec3 p_0, int level);
   bool isShadowed(vec3 shadowRay, vec3 p_1);
};

#endif