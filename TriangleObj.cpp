#include "TriangleObj.hpp"

TriangleObj::TriangleObj() {
   ObjID = -1;
}

TriangleObj::TriangleObj(int id) {
   ObjID = id;
}

TriangleObj::~TriangleObj() {}

ostream& operator<< (ostream &out, TriangleObj &triObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << triObj.corner1.x << ", " <<
                  triObj.corner1.y << ", " <<
                  triObj.corner1.z << ")";
    return out;
}


void TriangleObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   //char *token2;
   
   getline(povFile, line);
   
   getline(povFile, line);
   line2 = (char*)line.c_str();

   corner1.x = atof(strtok (line2,"{ <,>}"));
   corner1.y = atof(strtok (NULL,"{ <,>}"));
   corner1.z = atof(strtok (NULL,"{ <,>}"));
   
   getline(povFile, line);
   line2 = (char*)line.c_str();
     
   corner2.x = atof(strtok (line2,"{ <,>}"));
   corner2.y = atof(strtok (NULL,"{ <,>}"));
   corner2.z = atof(strtok (NULL,"{ <,>}")); 
   
   getline(povFile, line);
   line2 = (char*)line.c_str();
   
   corner3.x = atof(strtok (line2,"{ <,>}"));
   corner3.y = atof(strtok (NULL,"{ <,>}"));
   corner3.z = atof(strtok (NULL,"{ <,>}"));

   parseGeometry(povFile);
}
