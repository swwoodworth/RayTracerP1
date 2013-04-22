#include "LightSourceObj.hpp"

LightSourceObj::LightSourceObj() {
   ObjID = -1;
}

LightSourceObj::LightSourceObj(int id) {
   ObjID = id;
}

LightSourceObj::~LightSourceObj() {}

ostream& operator<< (ostream &out, LightSourceObj &lsObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << lsObj.location.x << ", " <<
                  lsObj.location.y << ", " <<
                  lsObj.location.z << ")";
    return out;
}


void LightSourceObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   
   cout << "I'm parsing a light source" << endl;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();
   
   location.x = atof(strtok (line2,"{ <,>}"));
   location.y = atof(strtok (NULL,"{ <,>}"));
   location.z = atof(strtok (NULL,"{ <,>}"));
   
   strtok (NULL,"{ <,>}"); // skip "color"
   strtok (NULL,"{ <,>}"); // skip "rgb"
   
   color.x = atof(strtok (NULL,"{ <,>}"));
   color.y = atof(strtok (NULL,"{ <,>}"));
   color.z = atof(strtok (NULL,"{ <,>}"));
   
   //color = normalize(color);
   
   //cout << "I'm done parsing a light source" << endl;

   return;
}
