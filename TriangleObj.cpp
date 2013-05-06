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

bool TriangleObj::intersect(vec3 d, vec3 p_0, float* t)
{
   float beta, gamma; //alpha
   mat3 alphaDet, betaDet, gammaDet, alphaInverse;
   vec3 betaVec, solution;
   
   float temp_01 = corner1.x - corner2.x;
   float temp_02 = corner1.y - corner2.y;
   float temp_03 = corner1.z - corner2.z;
   
   float temp_04 = corner1.x - corner3.x;
   float temp_05 = corner1.y - corner3.y;
   float temp_06 = corner1.z - corner3.z;
   
   float temp_07 = corner1.x - p_0.x;
   float temp_08 = corner1.y - p_0.y;
   float temp_09 = corner1.z - p_0.z;
   
   alphaDet = mat3( vec3(temp_01,temp_04,d.x),
                    vec3(temp_02,temp_05,d.y),
                    vec3(temp_03,temp_06,d.z) );
                    
   alphaInverse = glm::inverse(alphaDet);
   betaVec = vec3(temp_07, temp_08, temp_09);
   
   solution = alphaInverse*betaVec;
   
   beta = solution.x;
   gamma = solution.y;
   *t =solution.z;
   
   
   if(*t > 0.0 )
   {
      cout << beta << ", " << gamma << endl;
   }
   

   if(*t > 0.0 && beta >= 0 && beta <= 1 && gamma >=  0 && gamma <= 1) //if t > 0 and in the triangle
   {

      *t = solution.z;
      return true;
   }
   else 
      return false;
   
}

vec3 TriangleObj::getNormal(vec3 intersect) 
{
   vec3 temp = glm::cross(corner2 - corner1, corner3 - corner1);
   return normalize(temp);
}

