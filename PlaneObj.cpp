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
   pl = 1;
   cout << pl << endl;
   //char *token2;
   
   getline(povFile, line);
   line2 = (char*)line.c_str();

   normal.x = atof(strtok (line2,"{ <,>}"));
   normal.y = atof(strtok (NULL,"{ <,>}"));
   normal.z = atof(strtok (NULL,"{ <,>}"));  
   distance = atof(strtok (NULL,"{ <,>}"));  
            //cout << distance;

   center = normal * distance;

   parseGeometry(povFile);
}

bool PlaneObj::intersect(vec3 d, vec3 p_0, float* t)
{
   vec3 p = (normal / length(normal)) * distance;
   //cout << p.x << ", " << p.y << ", " << p.z << endl;
   
   //cout << dot((p-p_0), normal) << endl;
   //cout << dot(d, normal) << endl;
   *t = dot((p-p_0), normal)/dot(d, normal);
   //cout << *t << endl;
   if(*t>0.0)
      return true;
   else
      return false;
}

vec3 PlaneObj::getNormal(vec3 intersect) 
{
   //cout << "plane" << normal.x << ", " << normal.y << ", " << normal.z << endl;

   return normalize(normal);
}

