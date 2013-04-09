#include "RayTracerObject.hpp"

RayTracerObject::RayTracerObject() {
   ObjID = -1;
}

RayTracerObject::RayTracerObject(int id) {
   ObjID = id;
}

RayTracerObject::~RayTracerObject() {}