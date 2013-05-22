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


void SphereObj::parse(ifstream &povFile) 
{
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
   
   center = location;

   parseGeometry(povFile);
}

bool SphereObj::intersect(vec3 d, vec3 p_0, float* t)
{
   double a, b, c, discrim, t_1, t_2;
   
   vec3 e = (p_0 - location);
   
   a = dot(d,d);
   b = dot(2.0f*d, e);
   c = dot(e, e) - pow(radius,2);

   discrim = pow(b,2) - 4*a*c;
   if(discrim < 0)
      return false;
   else
   {
      t_1 = (-b + sqrt(discrim))/2*a;
      t_2 = (-b - sqrt(discrim))/2*a;
      if(std::min(t_1,t_2)>0.0)
      {
         *t = std::min(t_1,t_2);
         return true;
      }  
      else if (std::max(t_1,t_2)>0.0)
      {
         *t = std::max(t_1,t_2);
         return true;
      }
      else 
         return false;
   }

}

vec3 SphereObj::getNormal(vec3 intersect) 
{
   //cout << "here" << endl;
   return normalize(vec3(intersect - location));
}

vec3 SphereObj::getBBoxCorner1()
{
   //cout << location.x - radius - .00001 << endl;
   return vec3(location.x - radius - .00001,
               location.y - radius - .00001,
               location.z - radius - .00001);
}

vec3 SphereObj::getBBoxCorner2()
{
   return vec3(location.x + radius + .00001,
               location.y + radius + .00001,
               location.z + radius + .00001);
}

