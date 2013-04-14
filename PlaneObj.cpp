#include "PlaneObj.hpp"

PlaneObj::PlaneObj() {
   ObjID = -1;
}

PlaneObj::PlaneObj(int id) {
   ObjID = id;
}

PlaneObj::~PlaneObj() {}

ostream& operator<< (ostream &out, PlaneObj &planeObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << planeObj.normal.x << ", " <<
                  planeObj.normal.y << ", " <<
                  planeObj.normal.z << ")";
    return out;
}


void PlaneObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   //char *token2;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();

   normal.x = atof(strtok (line2,"{ <,>}"));
   normal.y = atof(strtok (NULL,"{ <,>}"));
   normal.z = atof(strtok (NULL,"{ <,>}"));  
   distance = atof(strtok (NULL,"{ <,>}"));  
            cout << distance;


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

double PlaneObj::intersect(vec3 d, vec3 p_0)
{
   vec3 p;
   double t;
   
   p = (normal / length(normal)) * distance;
   //cout << p.x << ", " << p.y << ", " << p.z << endl;
   
   //cout << dot((p-p_0), normal) << endl;
   //cout << dot(d, normal) << endl;
   t = dot((p-p_0), normal)/dot(d, normal);
   //cout << t << endl;
   return t;
}

