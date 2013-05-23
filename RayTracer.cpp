#include "RayTracer.hpp"

RayTracer::RayTracer() {
}

RayTracer::~RayTracer() {}

Geometry* intersectBBTree(BBox bBox, vec3 p_0, vec3 d, float* t);


void RayTracer::genRays()
{
   TGAWriter tga(screenWidth, screenHeight);
   float  u_s, v_s, w_s;
   float u_s_array[9], v_s_array[9];
   vec3 u, v, w, p_0, p_color, d, s_prime;
   
   p_0 = cameras[0]->location;
         
   //cout << p_0.x << ", " << p_0.y << ", " << p_0.z << endl;
   
   for (int i = 0; i < screenHeight; i++)
   {
      for (int j = 0; j < screenWidth; j++)
      {  
         p_color = vec3(0.0,0.0,0.0);
         if(antiAliasLevel == 0)
         {
            u_s = pixelToWorldX(j);
            v_s = pixelToWorldY(i);
            w_s = -1;
            //cout << i_x << ", " << i_y << endl;
            u = cameras[0]->right/ length(cameras[0]->right);
            v = cameras[0]->up/ length(cameras[0]->up);
            w =  cross(u, v);
         
            s_prime = p_0 + u_s*u + v_s*v + w_s*w;
         
            d = normalize(s_prime - p_0);
         
            p_color = raytrace(d, p_0, 0, 0);
         }
         else
         {
            if(antiAliasLevel == 4)
            {
               pixelToWorldXAA9(j, u_s_array);
               pixelToWorldYAA9(i, v_s_array);
            }
            if(antiAliasLevel == 9)
            {
               pixelToWorldXAA9(j, u_s_array);
               pixelToWorldYAA9(i, v_s_array);
            }
         
            w_s = -1;
         
            u = cameras[0]->right/ length(cameras[0]->right);
            v = cameras[0]->up/ length(cameras[0]->up);
            w =  cross(u, v);
         
            for(int k = 0; k < antiAliasLevel; k++)
            {
               s_prime = p_0 + u_s_array[k]*u + v_s_array[k]*v + w_s*w;
         
               d = normalize(s_prime - p_0);
         
               p_color += raytrace(d, p_0, 0, 0);
            }
            
            if(antiAliasLevel == 4)
               p_color /= 4.0f; 
            if(antiAliasLevel == 9)
               p_color /= 9.0f; 
         }
         
         //cout << p_color.x << ", " << p_color.y << ", " << p_color.z << endl;
         tga.colorPixel(i*(screenWidth) + j, p_color);
      }
      cout << i << endl;
   }
   
   tga.writeTGA(true);
}

vec3 RayTracer::raytrace(vec3 d, vec3 p_0, int reflectDepth, int refractDepth)
{
   vec3 intersect, objIntersect, norm, l_norm, v_norm, p_1, p_2, shadowRay;
   float t, reflect, refract, refractVal;
   float* addr = &t;
   bool temp;
   ShadingModel shadingModel;
   
   double depth = DBL_MAX;
   vec3 p_color = vec3(0.0,0.0,0.0); 
   
   Geometry *geom = intersectBBTree(rootBB, p_0, d, addr); 
   int k = findClosestPlane(p_0, d);
   if(k!=-1 && geom == NULL)
      geom = planes[k];
   if(k==-1 && geom == NULL)
      return p_color; //return black
   /*int k = findClosest(p_0, d);
   if(k==-1)
      return p_color; //return black*/
   else
   {
      mat4 m_i = geom->getTransformation();

      vec3 d_new = vec3(m_i * vec4(d,0));
      vec3 p_0_new = vec3(m_i * vec4(p_0,1));

      temp = geom->intersect(d_new, p_0_new, addr);
      if(temp == true && t > 0.0 && t < depth)
      {
         depth = t;

         mat4 m_i_t = transpose(m_i);
      
         reflect = geom->fObj->reflection;
         refract = geom->fObj->refraction;
         refractVal = geom->pObj->pigment.w;
      
         intersect = vec3(p_0 + (d * t));
         objIntersect = vec3(p_0_new + (d_new * t));

         //geometry normal
         norm = normalize(vec3(m_i_t*vec4(geom->getNormal(objIntersect), 0)));
         //if(k == 1)
         //  cout << norm.x << ", " << norm.y << ", " << norm.z << endl;

         //view vector
         v_norm = normalize(-d);
      
         // Move the intersect point slightly away so that it doesn't intersect itself
         //p_1 = intersect + shadowRay/2500.0f;
         p_1 = intersect + norm/2500.0f;
         
         for(int l = 0; l < (int) lights.size(); l++)
         {
            vec3 light = lights[l]->location;
            //light vector
            l_norm = normalize(light - intersect);
           
            shadowRay = normalize(light - p_1); 

            float distance = length(light - p_1);
            if(isShadowed(shadowRay, p_1, distance)) //set color to ambient
            {
               p_color += vec3(geom->fObj->ambient*geom->pObj->pigment.x*lights[l]->color.x,
                              geom->fObj->ambient*geom->pObj->pigment.y*lights[l]->color.y, 
                              geom->fObj->ambient*geom->pObj->pigment.z*lights[l]->color.z);
            }
            else
            {
               if(shadingMode == 0)  //Phong
                  p_color += shadingModel.phong(norm, l_norm, v_norm, geom, l);
               else if(shadingMode == 1)             // Gaussian Distribution Specular - some code from http://www.arcsynthesis.org/gltut/Illumination/Tut11%20Gaussian.html
                  p_color += shadingModel.gaussian(norm, l_norm, v_norm, geom, l);
            }
         }
         //p_color = l_norm;
         if(refract > 0.0 && refractDepth <  5 && reflectDepth < 5)
         {
            vec3 refractT;
            bool success = false;
            bool* successAddr = &success;
            float cos_theta, n1, n2;
            //float R, R_0;
         

            vec3 newD = d - 2.0f*dot(norm,d)*norm;
            vec3 p_3 = intersect + newD/2500.0f;
            //newD = vec3(m*vec4(newD, 0));
            //p_3 = vec3(m*vec4(p_3, 1));
            vec3 reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth);
         
            /*if(reflectedColor == vec3(0.0,0.0,0.0))
            {
               reflectedColor = p_color;
            }*/
         
            n2 = 1;
            n1 = geom->fObj->ior;
         
            if(dot(d_new, norm) < 0)
            {
               refractT = refractRay(d, norm, n2, n1, successAddr);
               cos_theta = dot(d, -norm);
            }
            else
            {
               refractT = refractRay(d, -norm, n1, n2, successAddr);
               if(success == true)
               {
                  cos_theta = dot(d, norm);
               }
               else
               {
                   p_color = reflectedColor;
               }
            }
         
            /*if(success == true)
            {
               R_0 = pow((n2 - n1), 2)/pow((n2 +  n1),2);
               R = R_0 + (1-R_0)*pow((1-cos_theta),5);
         
               p_2 = intersect + refractT/25000.0f;

               p_color = R*reflectedColor + (1-R)*raytrace(refractT,p_2,reflectDepth, refractDepth+1);
            }*/
            if(success == true)
            {
               p_2 = intersect + refractT/2500.0f;
               //refractT = vec3(m*vec4(refractT,0));
               //p_2 = vec3(m*vec4(p_2,1));
               p_color = (1-reflect-refractVal)*p_color + reflect*reflectedColor + refractVal*raytrace(refractT,p_2,reflectDepth+1, refractDepth+1);
            }
         }
      
         else if(reflect > 0.0 && reflectDepth < 5)
         {
            vec3 newD = d - 2.0f*dot(norm,d)*norm;
            vec3 p_3 = intersect + newD/2500.0f;
            //newD = vec3(m*vec4(newD, 0));
            //p_3 = vec3(m*vec4(p_3, 1));
            vec3 reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth);
            if(reflectedColor != vec3(0.0,0.0,0.0))
            {
               p_color = (1-reflect)*p_color + (reflect)*reflectedColor;
            }
         }
      }
      //cout << p_color.x << ", " << p_color.y << ", " << p_color.z << endl;
   }
   return p_color;
}

int RayTracer::findClosest(vec3 p_0, vec3 d)
{
   double depth = DBL_MAX;
   int closest = -1;
   bool temp = false;
   float t;
   float* addr = &t;
   
   for(int k = 0; k < (int) geometry.size(); k++)
   {
      mat4 m_i = geometry[k]->getTransformation();

      vec3 d_new = vec3(m_i * vec4(d,0));
      vec3 p_0_new = vec3(m_i * vec4(p_0,1));

      temp = geometry[k]->intersect(d_new, p_0_new, addr);
      if(temp == true && t > 0.0 && t < depth)
      {
         depth = t;
         closest = k;
      }
   }
   //if(closest != -1)
   //cout << closest << endl;
   return closest;
}

int RayTracer::findClosestPlane(vec3 p_0, vec3 d)
{
   double depth = DBL_MAX;
   int closest = -1;
   bool temp = false;
   float t;
   float* addr = &t;
   
   for(int k = 0; k < (int) planes.size(); k++)
   {
      mat4 m_i = planes[k]->getTransformation();

      vec3 d_new = vec3(m_i * vec4(d,0));
      vec3 p_0_new = vec3(m_i * vec4(p_0,1));

      temp = planes[k]->intersect(d_new, p_0_new, addr);
      if(temp == true && t > 0.0 && t < depth)
      {
         depth = t;
         closest = k;
      }
   }
   //if(closest != -1)
   //cout << closest << endl;
   return closest;
}

bool RayTracer::isShadowed(vec3 shadowRay, vec3 p_1, float distance)
{
   //bool temp = false;
   float t;
   float* addr = &t;

   //cout << "shadow ray " << shadowRay.x << ", " << shadowRay.y << ", " << shadowRay.z << endl;
   //cout << p_1.x << ", " << p_1.y << ", " << p_1.z << endl;
   
   Geometry *geom = intersectBBTree(rootBB, p_1, shadowRay, addr); 
   if(geom != NULL && t > 0 && t < distance)
         return true;
   /*for(int k = 0; k < (int) geometry.size(); k++)
   {
      mat4 m_i = geometry[k]->getTransformation();
      
      vec3 d_new = vec3(m_i * vec4(shadowRay,0));
      vec3 p_0_new = vec3(m_i * vec4(p_1,1));
      
      temp = geometry[k]->intersect(d_new, p_0_new, addr);
      
      if(temp && t > 0 && t < distance)
         return true;
   }    */
   return false;       
}

vec3 RayTracer::refractRay(vec3 d, vec3 norm, float n_1, float n_2, bool* success)
{
   vec3 t;
   
   float inner = 1 - pow((n_1/n_2), 2) * (1 - pow(dot(d,norm),2));
   if(inner >= 0)
   {
      *success = true;
      t = n_1/n_2*(d-norm*dot(d,norm))-norm*sqrt(inner);
   }
   else
   {
      *success = false;
   }
   
   return t;
}


double RayTracer::pixelToWorldX(int in_x) {
   double l = -length(cameras[0]->right)/2.0;
   double r = length(cameras[0]->right)/2.0;
   return l + (r-l)*(in_x+.5)/screenWidth;
}

double RayTracer::pixelToWorldY(int in_y) {
   double b = -length(cameras[0]->up)/2.0;
   double t = length(cameras[0]->up)/2.0;
   return b + (t-b)*(in_y+.5)/screenHeight;
}

// generates an array of 4 anti-aliased ray positions
void RayTracer::pixelToWorldXAA4(int in_x, float *array) {
   double l = -length(cameras[0]->right)/2.0;
   double r = length(cameras[0]->right)/2.0;
   
   array[0] = l + (r-l)*(in_x+.25)/screenWidth;
   array[1] = l + (r-l)*(in_x+.75)/screenWidth;
   array[2] = l + (r-l)*(in_x+.25)/screenWidth;
   array[3] = l + (r-l)*(in_x+.75)/screenWidth;
}

void RayTracer::pixelToWorldYAA4(int in_y, float *array) {
   double b = -length(cameras[0]->up)/2.0;
   double t = length(cameras[0]->up)/2.0;
   
   array[0] = b + (t-b)*(in_y+.25)/screenHeight;
   array[1] = b + (t-b)*(in_y+.75)/screenHeight;
   array[2] = b + (t-b)*(in_y+.25)/screenHeight;
   array[3] = b + (t-b)*(in_y+.75)/screenHeight;
}

// generates an array of 9 anti-aliased ray positions
void RayTracer::pixelToWorldXAA9(int in_x, float *array) {
   double l = -length(cameras[0]->right)/2.0;
   double r = length(cameras[0]->right)/2.0;
   
   array[0] = l + (r-l)*(in_x+.1666)/screenWidth;
   array[1] = l + (r-l)*(in_x+.5)/screenWidth;
   array[2] = l + (r-l)*(in_x+.8333)/screenWidth;
   
   array[3] = l + (r-l)*(in_x+.1666)/screenWidth;
   array[4] = l + (r-l)*(in_x+.5)/screenWidth;
   array[5] = l + (r-l)*(in_x+.8333)/screenWidth;
   
   array[6] = l + (r-l)*(in_x+.1666)/screenWidth;
   array[7] = l + (r-l)*(in_x+.5)/screenWidth;
   array[8] = l + (r-l)*(in_x+.8333)/screenWidth;
}

void RayTracer::pixelToWorldYAA9(int in_y, float *array) {
   double b = -length(cameras[0]->up)/2.0;
   double t = length(cameras[0]->up)/2.0;
   
   array[0] = b + (t-b)*(in_y+.1666)/screenHeight;
   array[1] = b + (t-b)*(in_y+.5)/screenHeight;
   array[2] = b + (t-b)*(in_y+.8333)/screenHeight;
   
   array[3] = b + (t-b)*(in_y+.1666)/screenHeight;
   array[4] = b + (t-b)*(in_y+.5)/screenHeight;
   array[5] = b + (t-b)*(in_y+.8333)/screenHeight;
   
   array[6] = b + (t-b)*(in_y+.1666)/screenHeight;
   array[7] = b + (t-b)*(in_y+.5)/screenHeight;
   array[8] = b + (t-b)*(in_y+.8333)/screenHeight;
}

Geometry* intersectBBTree(BBox bBox, vec3 p_0, vec3 d, float* t)
{
   if(bBox.intersect(d,p_0,t))
   {
      //cout << "hit" << endl;
      if(bBox.geometry != NULL) // at a leaf
      {
         mat4 m_i = bBox.geometry->getTransformation();

         vec3 d_new = vec3(m_i * vec4(d,0));
         vec3 p_0_new = vec3(m_i * vec4(p_0,1));

         bool temp = bBox.geometry->intersect(d_new, p_0_new, t);
         if(temp != true)
            return NULL;
         else
            return bBox.geometry;
      }
      else
      {
         Geometry *g1 = intersectBBTree(*bBox.left, p_0, d, t);
         float t_left = *t;
         Geometry *g2 = intersectBBTree(*bBox.right, p_0, d, t);
         float t_right = *t;
         if(g1 != NULL && g2 != NULL) //check which is closer
         {
            if(t_left < t_right)   // left is closer
            {
               *t = t_left;
               return g1;
            }
            else
            {
               *t = t_right;
               return g2;
            }
         }
         else if (g1 != NULL && g2 == NULL)  //only hit left
         {
            *t = t_left;
            return g1;
         }
         else if (g1 == NULL && g2 != NULL)  //only hit right
         {
            *t = t_right;
            return g2;
         }
         else                                //didn't hit either
            return NULL;
      }
   }
   else
   {
      //cout << "miss" << endl;
      return NULL;
   }
}

