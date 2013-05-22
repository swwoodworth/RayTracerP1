#include "BBox.hpp"

BBox::BBox() {
}

BBox::BBox(Geometry *g) {
   geometry = g;
   left = NULL;
   right = NULL;
   corner1 = g->getBBoxCorner1();
   corner2 = g->getBBoxCorner2();
   buildBB();
   transformBB();
   cout << c[4].x << " " << c[4].y << " " << c[4].z << endl;
   cout << c[2].x << " " << c[2].y << " " << c[2].z << endl;
}

BBox::BBox(BBox *l, BBox *r) {
   geometry = NULL;
   left = l;
   right = r;
   corner1 = min(left->corner1, right->corner1);
   corner2 = max(left->corner2, right->corner2);
   buildBB();
}

BBox::~BBox() {}

ostream& operator<< (ostream &out, BBox &bBox)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << bBox.corner1.x << ", " <<
                  bBox.corner1.y << ", " <<
                  bBox.corner1.z << ")";
    return out;
}

bool BBox::intersect(vec3 d, vec3 p_0, float* t)
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
   {
      return false;
   }
   
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
   {
      return false;
   }
}

vec3 BBox::getNormal(vec3 intersect) 
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

void BBox::buildBB()
{
   c[0] = vec3(corner1.x, corner1.y, corner2.z);
   c[1] = vec3(corner1.x, corner2.y, corner2.z);
   c[2] = vec3(corner2.x, corner2.y, corner2.z);
   c[3] = vec3(corner2.x, corner1.y, corner2.z);
   c[4] = vec3(corner1.x, corner1.y, corner1.z);
   c[5] = vec3(corner1.x, corner2.y, corner1.z);
   c[6] = vec3(corner2.x, corner2.y, corner1.z);
   c[7] = vec3(corner2.x, corner1.y, corner1.z);
}

void BBox::transformBB()
{
   mat4 m_i = geometry->getTransformation();
      
   c[0] = vec3(m_i* vec4(c[0],1));
   c[1] = vec3(m_i* vec4(c[1],1));
   c[2] = vec3(m_i* vec4(c[2],1));
   c[3] = vec3(m_i* vec4(c[3],1));
   c[4] = vec3(m_i* vec4(c[4],1));
   c[5] = vec3(m_i* vec4(c[5],1));
   c[6] = vec3(m_i* vec4(c[6],1));
   c[7] = vec3(m_i* vec4(c[7],1));
}




