#include "RotateObj.hpp"

RotateObj::RotateObj() {
   ObjID = -1;
}

RotateObj::RotateObj(int id) {
   ObjID = id;
}

RotateObj::~RotateObj() {}

ostream& operator<< (ostream &out, RotateObj &rObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << rObj.rotation.x << ", " <<
                  rObj.rotation.y << ", " <<
                  rObj.rotation.z << ")";
    return out;
}


void RotateObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
      
   getline(povFile, line);
   line2 = (char*)line.c_str();
   
   rotation.x = atof(strtok (line2," <,>"));
   rotation.y = atof(strtok (NULL," <,>"));
   rotation.z = atof(strtok (NULL," <,>"));

   return;
}

mat4 RotateObj::getRotate() {
   mat4 transformation(1.0f);
   
   if(rotation.x != 0)
      transformation = rotate(mat4(1.0f),rotation.x, vec3(1.0,0.0,0.0));
   else if(rotation.y != 0)
      transformation = rotate(mat4(1.0f),rotation.y, vec3(0.0,1.0,0.0));
   else if(rotation.z != 0)
      transformation = rotate(mat4(1.0f),rotation.z, vec3(0.0,0.0,1.0));
   return transformation;
}
