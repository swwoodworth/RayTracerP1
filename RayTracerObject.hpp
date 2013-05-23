#ifndef RTO_H
#define RTO_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class RayTracerObject {
  public:
   RayTracerObject(); //default constructor
   RayTracerObject(int id); //alternate constructor
   ~RayTracerObject(); //destructor
   virtual void parse(ifstream &povFile) {cout << "Parse is not implemented for this object" << endl;}; //base class parse function
   int ObjID;
};

#endif