#include "SphereObj.hpp"

SphereObj::SphereObj() {
   pObj = NULL;
   fObj = NULL;
   tObj = NULL;
   sObj = NULL;
   rObj = NULL;
   ObjID = -1;
}

SphereObj::SphereObj(int id) {
   pObj = NULL;
   fObj = NULL;
   tObj = NULL;
   sObj = NULL;
   rObj = NULL;
   ObjID = id;
}

SphereObj::~SphereObj() {}

ostream& operator<< (ostream &out, SphereObj &sphereObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << sphereObj.location.x << ", " <<
                  sphereObj.location.y << ", " <<
                  sphereObj.location.z << ") ";
    out <<  sphereObj.radius << " ";
    if (sphereObj.sObj != NULL)
       out <<  (*sphereObj.sObj) << " ";
    if (sphereObj.fObj != NULL)
       out <<  (*sphereObj.fObj) << " ";
    if (sphereObj.tObj != NULL)
       out <<  (*sphereObj.tObj) << " ";
    if (sphereObj.sObj != NULL)
       out <<  (*sphereObj.sObj) << " ";
    if (sphereObj.rObj != NULL)
       out <<  (*sphereObj.rObj) << " ";
    return out;
}


void SphereObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   //char *token2;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();

   location.x = atof(strtok (line2,"{ <,>}"));
   location.y = atof(strtok (NULL,"{ <,>}"));
   location.z = atof(strtok (NULL,"{ <,>}"));  
   radius = atof(strtok (NULL,"{ <,>}"));  

   while(povFile.good()) // check if at eof
   {
      povFile >> token;

      if(token.compare("}") == 0)
         return; // found end of parameters
      else if(token.compare("pigment") == 0)
      {
         pObj = new PigmentObj();
         pObj->parse(povFile);
      }
      else if(token.compare("finish") == 0)
      {
         fObj = new FinishObj();
         fObj->parse(povFile);
      }
      else if(token.compare("translate") == 0)
      {
         tObj = new TranslateObj();
         tObj->parse(povFile);
      }
      else if(token.compare("scale") == 0)
      {
         sObj = new ScaleObj();
         sObj->parse(povFile);
      }
      else if(token.compare("rotate") == 0)
      {
         rObj = new RotateObj();
         rObj->parse(povFile);
      }
   }
}
