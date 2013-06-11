#include "PigmentObj.hpp"

PigmentObj::PigmentObj() {
   ObjID = -1;
}

PigmentObj::PigmentObj(int id) {
   ObjID = id;
}

PigmentObj::~PigmentObj() {}

ostream& operator<< (ostream &out, PigmentObj &pObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << pObj.pigment.x << ", " <<
                  pObj.pigment.y << ", " <<
                  pObj.pigment.z << ", " <<
                  pObj.pigment.w << ")";
    return out;
}


void PigmentObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();
   
   strtok (line2,"{ <,>}"); // skip "color"
   token = strtok (NULL,"{ <,>}"); // check if rgb or rgbf
   
   pigment.x = atof(strtok (NULL," <,>"));
   pigment.y = atof(strtok (NULL," <,>"));
   pigment.z = atof(strtok (NULL," <,>"));
   
   //cout << pigment.x << endl;
   
   if(token.compare("rgbf") == 0)
      pigment.w = atof(strtok (NULL," <,>"));
   else
      pigment.w = 0.0;
   //cout << pigment.w << endl;
      
   return;
}
