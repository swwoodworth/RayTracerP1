#include "ScaleObj.hpp"

ScaleObj::ScaleObj() {
   ObjID = -1;
}

ScaleObj::ScaleObj(int id) {
   ObjID = id;
}

ScaleObj::~ScaleObj() {}

ostream& operator<< (ostream &out, ScaleObj &sObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << sObj.scale.x << ", " <<
                  sObj.scale.y << ", " <<
                  sObj.scale.z << ")";
    return out;
}


void ScaleObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
      
   getline(povFile, line);
   line2 = (char*)line.c_str();

   //cout << line << endl;
   if(line.compare(0,2," <") == 0)    // check if scale is in format <x,y,z> or value
   {  
      scale.x = atof(strtok (line2," <,>"));
      scale.y = atof(strtok (NULL," <,>"));
      scale.z = atof(strtok (NULL," <,>"));
      //cout << "else" << endl;

   }
   else
   {
      scale.x = scale.y = scale.z = atof(strtok (line2," ,"));
      //cout << scale.x << endl;
   }
   //cout << scale.x << " " << scale.y << " " << scale.z << endl;

   return;
}

mat4 ScaleObj::getScale() {

   mat4 transformation = glm::scale(mat4(1.0f),scale);
   //cout << scale.x << " " << scale.
   return transformation;
}

