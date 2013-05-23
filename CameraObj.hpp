#ifndef CAMERA_H
#define CAMERA_H

#include "RayTracerObject.hpp"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

using namespace std;
using namespace glm;

class CameraObj : public RayTracerObject {
  public:
    CameraObj();
    CameraObj(int id);
    ~CameraObj();
    void parse(ifstream &povFile);
    friend ostream& operator<< (ostream &out, CameraObj &cObj);    
    vec3 location;
    vec3 up;
    vec3 right;
    vec3 lookAt;
    
};

#endif