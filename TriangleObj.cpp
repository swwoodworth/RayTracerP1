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
   if(line == "" || line.compare(" {") == 0)
   {
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
   }
   else
   {
      line2 = (char*)line.c_str();
      //cout << line2  << endl;
      corner1.x = atof(strtok (line2,"{ <,>}"));
      corner1.y = atof(strtok (NULL,"{ <,>}"));
      corner1.z = atof(strtok (NULL,"{ <,>}"));
     
      corner2.x = atof(strtok (NULL,"{ <,>}"));
      corner2.y = atof(strtok (NULL,"{ <,>}"));
      corner2.z = atof(strtok (NULL,"{ <,>}")); 
   
      corner3.x = atof(strtok (NULL,"{ <,>}"));
      corner3.y = atof(strtok (NULL,"{ <,>}"));
      corner3.z = atof(strtok (NULL,"{ <,>}"));
   }
   
   center = (corner1 + corner2 + corner3)/3.0f;

   parseGeometry(povFile);
}

bool TriangleObj::intersect(vec3 d, vec3 p_0, float* t)
{  
   //cout << "intersect" << endl;
   float a = corner1.x - corner2.x;
   float b = corner1.y - corner2.y;
   float c = corner1.z - corner2.z;
   
   float d1 = corner1.x - corner3.x;
   float e = corner1.y - corner3.y;
   float f = corner1.z - corner3.z;
   
   float g = d.x;
   float h = d.y;
   float i = d.z;
   
   float j = corner1.x - p_0.x;
   float k = corner1.y - p_0.y;
   float l = corner1.z - p_0.z;
   
   float M = a*(e*i - h*f) + b*(g*f - d1*i) + c*(d1*h - e*g);
   
   *t = -(f*(a*k - j*b) + e*(j*c - a*l) + d1*(b*l - k*c))/M;
   
   if(*t <= 0)
      return false;
   //cout << "past t" << endl;
   float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
   
   if (gamma < 0 || gamma > 1)
      return false;
   //cout << "past gamma" << endl;

   float beta = (j*(e*i - h*f) + k*(g*f - d1*i) + l*(d1*h - e*g))/M;
   
   if (beta < 0 || beta > 1 - gamma)
      return false;
   
   return true;  
}

/*bool TriangleObj::intersect(vec3 d, vec3 p_0, float* t)
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
   
}*/

vec3 TriangleObj::getNormal(vec3 intersect) 
{
   vec3 temp = glm::cross(corner2 - corner1, corner3 - corner1);
   temp = normalize(temp);
   //cout << temp.x << ", " << temp.y << ", " << temp.z << endl;
   return normalize(temp);
}

vec3 TriangleObj::getBBoxCorner1()
{
   float minx = std::min(std::min(corner1.x, corner2.x), corner3.x) - .00001;
   float miny = std::min(std::min(corner1.y, corner2.y), corner3.y) - .00001;
   float minz = std::min(std::min(corner1.z, corner2.z), corner3.z) - .00001;
   return vec3(minx,miny,minz);
}

vec3 TriangleObj::getBBoxCorner2()
{
   float maxx = std::max(std::max(corner1.x, corner2.x), corner3.x) + .00001;
   float maxy = std::max(std::max(corner1.y, corner2.y), corner3.y) + .00001;
   float maxz = std::max(std::max(corner1.z, corner2.z), corner3.z) + .00001;
   return vec3(maxx,maxy,maxz);
}

