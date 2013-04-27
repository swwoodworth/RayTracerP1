#include "BoxObj.hpp"

BoxObj::BoxObj() {
   ObjID = -1;
}

BoxObj::BoxObj(int id) {
   ObjID = id;
}

BoxObj::~BoxObj() {}

ostream& operator<< (ostream &out, BoxObj &boxObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << boxObj.corner1.x << ", " <<
                  boxObj.corner1.y << ", " <<
                  boxObj.corner1.z << ")";
    return out;
}


void BoxObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   //char *token2;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();

   corner1.x = atof(strtok (line2,"{ <,>}"));
   corner1.y = atof(strtok (NULL,"{ <,>}"));
   corner1.z = atof(strtok (NULL,"{ <,>}"));  
   corner2.x = atof(strtok (NULL,"{ <,>}"));
   corner2.y = atof(strtok (NULL,"{ <,>}"));
   corner2.z = atof(strtok (NULL,"{ <,>}")); 

   parseGeometry(povFile);
}
