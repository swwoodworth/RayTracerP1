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

bool BoxObj::intersect(vec3 d, vec3 p_0, float* t)
{
   float tmin,tmax,txmin,txmax,tymin,tymax,tzmin,tzmax;

   if(d.x >= 0)
   {
      txmin = (corner1.x - p_0.x)/d.x;
      txmax = (corner2.x - p_0.x)/d.x;
   }
   else
   {
      txmin = (corner2.x - p_0.x)/d.x;
      txmax = (corner1.x - p_0.x)/d.x;
   }
   
   if(d.y >= 0)
   {
      tymin = (corner1.y - p_0.y)/d.y;
      tymax = (corner2.y - p_0.y)/d.y;
   }
   else
   {
      tymin = (corner2.y - p_0.y)/d.y;
      tymax = (corner1.y - p_0.y)/d.y;
   }
   
   if( (txmin > tymax) || (tymin > txmax) )
      return false;
      
   if (tymin > txmin)
      tmin = tymin;
   else
      tmin = txmin;
      
   if (tymax < txmax)
      tmax = tymax;
   else 
      tmax = txmax;
      
   if(d.z >= 0)
   {
      tzmin = (corner1.z - p_0.z)/d.z;
      tzmax = (corner2.z - p_0.z)/d.z;
   }
   else
   {
      tzmin = (corner2.z - p_0.z)/d.z;
      tzmax = (corner1.z - p_0.z)/d.z;
   }
   
   if( (tmin > tzmax) || (tzmin > tmax) )
      return false;
   
   if (tzmin > tmin)
      tmin = tzmin;
      
   if (tzmax < tmax)
      tmax = tzmax;
  
   if (tmax > 0 && tmin > 0)
   {
      *t = tmin;
      return true;
   }
   else if (tmax > 0)
   {
      *t = tmax;
      return true;
   }
   else
      return false;
}

vec3 BoxObj::getNormal(vec3 intersect) 
{
   if( intersect.x > corner1.x-.00001 && intersect.x < corner1.x+.00001 )
      return vec3(-1,0,0);
   else if( intersect.x > corner2.x-.00001 && intersect.x < corner2.x+.00001 )
      return vec3(1,0,0);
   else if( intersect.y > corner1.y-.00001 && intersect.y < corner1.y+.00001 )
      return vec3(0,-1,0);
   else if( intersect.y > corner2.y-.00001 && intersect.y < corner2.y+.00001 )
      return vec3(0,1,0);
   else if( intersect.z > corner1.z-.00001 && intersect.z < corner1.z+.00001 )
      return vec3(0,0,-1);
   else if( intersect.z > corner2.z-.00001 && intersect.z < corner2.z+.00001 )
      return vec3(0,0,1);
   cout << "Error in box normal" << endl;
   return vec3(1,0,0);
}


