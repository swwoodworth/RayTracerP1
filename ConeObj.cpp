#include "ConeObj.hpp"

ConeObj::ConeObj() {
   ObjID = -1;
}

ConeObj::ConeObj(int id) {
   ObjID = id;
}

ConeObj::~ConeObj() {}

ostream& operator<< (ostream &out, ConeObj &coneObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << coneObj.end1.x << ", " <<
                  coneObj.end1.y << ", " <<
                  coneObj.end1.z << ")";
    return out;
}


void ConeObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   //char *token2;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();

   end1.x = atof(strtok (line2,"{ <,>}"));
   end1.y = atof(strtok (NULL,"{ <,>}"));
   end1.z = atof(strtok (NULL,"{ <,>}"));  
   radius1 = atof(strtok (NULL,"{ <,>}"));  
   
   end2.x = atof(strtok (NULL,"{ <,>}"));
   end2.y = atof(strtok (NULL,"{ <,>}"));
   end2.z = atof(strtok (NULL,"{ <,>}")); 
   radius2 = atof(strtok (NULL,"{ <,>}")); 

   parseGeometry(povFile);
}
