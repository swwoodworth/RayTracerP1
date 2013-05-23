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
#include "ShadingModel.hpp"
#include "BBox.hpp"


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

extern BBox rootBB;


extern int screenWidth;
extern int screenHeight;
extern int shadingMode;
extern int antiAliasLevel;


class RayTracer {
  public:
   RayTracer(); //default constructor
   ~RayTracer(); //destructor
   void genRays();
   vec3 raytrace(vec3 d, vec3 p_0, int reflectDepth, int refractDepth);
   int findClosest(vec3 p_0, vec3 d);
   int findClosestPlane(vec3 p_0, vec3 d);
   bool isShadowed(vec3 shadowRay, vec3 p_1, float distance);
   vec3 refractRay(vec3 d, vec3 norm, float n_1, float n_2, bool* success);
   double pixelToWorldX(int in_x);
   double pixelToWorldY(int in_y);
   void pixelToWorldXAA4(int in_x, float *array);
   void pixelToWorldYAA4(int in_y, float *array);
   void pixelToWorldXAA9(int in_x, float *array);
   void pixelToWorldYAA9(int in_y, float *array);

};

#endif