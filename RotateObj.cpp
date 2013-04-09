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
