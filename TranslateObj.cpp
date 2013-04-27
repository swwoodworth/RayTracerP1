#include "TranslateObj.hpp"

TranslateObj::TranslateObj() {
   ObjID = -1;
   translation = vec3(0.0,0.0,0.0);
}

TranslateObj::TranslateObj(int id) {
   ObjID = id;
   translation = vec3(0.0,0.0,0.0);
}

TranslateObj::~TranslateObj() {}

ostream& operator<< (ostream &out, TranslateObj &tObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << tObj.translation.x << ", " <<
                  tObj.translation.y << ", " <<
                  tObj.translation.z << ")";
    return out;
}


void TranslateObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
      
   getline(povFile, line);
   line2 = (char*)line.c_str();
   
   translation.x = atof(strtok (line2," <,>"));
   translation.y = atof(strtok (NULL," <,>"));
   translation.z = atof(strtok (NULL," <,>"));

   return;
}

mat4 TranslateObj::getTranslate(){

   mat4 transformation = translate(mat4(1.0f),translation);
   return transformation;
}
