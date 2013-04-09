#include "FinishObj.hpp"

FinishObj::FinishObj() {
   ObjID = -1;
}

FinishObj::FinishObj(int id) {
   ObjID = id;
}

FinishObj::~FinishObj() {}

ostream& operator<< (ostream &out, FinishObj &fObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << fObj.ambient << ", " <<
           fObj.diffuse << ", " <<
           fObj.specular;
    return out;
}


void FinishObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   char *token2;
      
   getline(povFile, line);
   line2 = (char*)line.c_str();
   
   token2 = strtok (line2,"{ <,>}");
   while (token2 != NULL)
   {
      token = token2;
      if(token.compare("ambient") == 0)
         ambient = atof(strtok (NULL,"{ <,>}"));
      else if(token.compare("diffuse") == 0)
         diffuse = atof(strtok (NULL,"{ <,>}"));
      else if(token.compare("specular") == 0)
         specular = atof(strtok (NULL,"{ <,>}"));
      else if(token.compare("roughness") == 0)
         roughness = atof(strtok (NULL,"{ <,>}"));
      else if(token.compare("reflection") == 0)
         reflection = atof(strtok (NULL,"{ <,>}"));
      else if(token.compare("refraction") == 0)
         refraction = atof(strtok (NULL,"{ <,>}"));
      else if(token.compare("ior") == 0)
         ior = atof(strtok (NULL,"{ <,>}"));
      token2 = strtok (NULL,"{ <,>}");
   }
   
   return;
}
