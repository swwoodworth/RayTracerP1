#include "RayTracer.hpp"

RayTracer::RayTracer() {
}

RayTracer::~RayTracer() {}

Geometry* intersectBBTree(BBox bBox, vec3 p_0, vec3 d, float* t);


void RayTracer::genRays()
{
   TGAWriter tga(screenWidth, screenHeight);
   float  w_s;
   float u_s_array[9], v_s_array[9];
   vec3 u, v, w, p_0, p_color, d, s_prime;
   
   p_0 = cameras[0]->location;
         
   //cout << p_0.x << ", " << p_0.y << ", " << p_0.z << endl;
   
   for (int i = 0; i < screenHeight; i++)
   {
      for (int j = 0; j < screenWidth; j++)
      {  
         p_color = vec3(0.0,0.0,0.0);
         if(antiAliasLevel == 1)
         {
            u_s_array[0] = pixelToWorldX(j);
            v_s_array[0] = pixelToWorldY(i);
         }
         
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
            
            /*if(i == 280 && j == 320)
               p_color += raytrace(d, p_0, 0, 0, 1);
            else */
               p_color += raytrace(d, p_0, 0, 0, 0, 0);
         }
         
         if(antiAliasLevel == 4)
            p_color /= 4.0f; 
         if(antiAliasLevel == 9)
            p_color /= 9.0f; 
         
         //cout << p_color.x << ", " << p_color.y << ", " << p_color.z << endl;
         /*if(i == 280 && j == 320)
         {
            cout << "Final Color: "  << p_color.x << ", " << p_color.y << ", " << p_color.z << endl;
            tga.colorPixel(i*(screenWidth) + j, vec3(0,0,0));
         }
         else*/
            tga.colorPixel(i*(screenWidth) + j, p_color);
      }
      cout << i << endl;
   }
   
   tga.writeTGA(true);
}

vec3 RayTracer::raytrace(vec3 d, vec3 p_0, int reflectDepth, int refractDepth, int print, int globalIll)
{
   vec3 intersect, objIntersect, norm, l_norm, v_norm, p_1, p_2, shadowRay, globalIllAmbient, ambient;
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
      //Geometry *geom = geometry[k];
      mat4 m_i = geom->getTransformation();

      vec3 d_new = vec3(m_i * vec4(d,0));
      vec3 p_0_new = vec3(m_i * vec4(p_0,1));

      temp = geom->intersect(d_new, p_0_new, addr);
      if(temp == true && t > 0.0 && t < depth)
      {
         if (print == 1)
            cout << "Init Direction " << print << " : "  << d_new.x << ", " << d_new.y << ", " << d_new.z << endl;
         depth = t;

         mat4 m_i_t = transpose(m_i);
      
         reflect = geom->fObj->reflection;
         refract = geom->fObj->refraction;
         refractVal = geom->pObj->pigment.w;
      
         intersect = vec3(p_0 + (d * t));
         if (print >= 1)
            cout << "Intersect " << print << " : "  << intersect.x << ", " << intersect.y << ", " << intersect.z << endl;
         
         objIntersect = vec3(p_0_new + (d_new * t));
         objIntersect = vec3(m_i*(vec4(intersect, 1)));

         //geometry normal
         norm = normalize(vec3(m_i_t*vec4(geom->getNormal(objIntersect), 0)));
         //return norm;
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
            
            if(globalIll > 0)
            {
               globalIllAmbient = vec3(0,0,0);
               for (int r = 0; r < 256; r++)
               {
                  float u1 = ((float) rand() / (RAND_MAX));
                  float u2 = ((float) rand() / (RAND_MAX));
                  vec3 hemisRay = cosineSampleHemisphere(u1,u2);
                  hemisRay = hemisphereToNormalTransform(hemisRay, norm);
                  globalIllAmbient += raytrace(hemisRay, p_1, 0, 0, 0, globalIll-1);
               }
               globalIllAmbient /= 256.0f;
               globalIllAmbient *= geom->fObj->ambient;
               //cout << globalIllAmbient.x << " " << globalIllAmbient.y << " " << globalIllAmbient.z << endl;
            }
            else
               ambient = geom->fObj->ambient*vec3(geom->pObj->pigment)*lights[l]->color;
            
            if(isShadowed(shadowRay, p_1, distance)) //set color to ambient
            {
               if(globalIll > 0)
                  p_color += globalIllAmbient;
               else
                  p_color += ambient;
            }
            else
            {
               if(shadingMode == 0)  //Phong
                  if(globalIll > 0)
                     p_color += shadingModel.phong(intersect, norm, l_norm, v_norm, geom, l, globalIllAmbient);
                  else
                     p_color += shadingModel.phong(intersect, norm, l_norm, v_norm, geom, l, ambient);
               else if(shadingMode == 1)             // Gaussian Distribution Specular - some code from http://www.arcsynthesis.org/gltut/Illumination/Tut11%20Gaussian.html
                  if(globalIll > 0)
                     p_color += shadingModel.gaussian(intersect, norm, l_norm, v_norm, geom, l, globalIllAmbient);
                  else
                     p_color += shadingModel.gaussian(intersect, norm, l_norm, v_norm, geom, l, ambient);
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
            //cout << "in refract " << geom->fObj->refraction << endl; 

            vec3 newD = d - 2.0f*dot(norm,d)*norm;
            vec3 p_3 = intersect + newD/2500.0f;
            //newD = vec3(m*vec4(newD, 0));
            //p_3 = vec3(m*vec4(p_3, 1));
      
            vec3 reflectedColor;
            /*if(print >= 1)
            {
               reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth+1, print+1);
            }
            else*/
            {
               reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth, 0, globalIll-1);
            }
         
            /*if(reflectedColor == vec3(0.0,0.0,0.0))
            {
               reflectedColor = p_color;
            }*/
         
            n2 = 1;
            n1 = geom->fObj->ior;
         
            if(dot(d, norm) < 0)
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
            //cout << refractT.x << " " << refractT.y << " " << refractT.z << endl;
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
               if(print >= 1)
               {
                  cout << "Refract Direction " << print << " : "  << refractT.x << ", " << refractT.y << ", " << refractT.z << endl;
                  vec3 refractColor = raytrace(refractT,p_2,reflectDepth+1, refractDepth+1, print+1, globalIll-1);
                  p_color = (1-reflect-refractVal)*p_color + reflect*reflectedColor + refractVal*refractColor;
               }
               else
               {
                  vec3 refractColor = raytrace(refractT,p_2,reflectDepth+1, refractDepth+1, 0, globalIll-1);
                  //cout << "Refract color: " << refractColor.x << refractColor.y << refractColor.z << endl;
                  p_color = (1-reflect-refractVal)*p_color + reflect*reflectedColor + refractVal*refractColor;
                  //cout << ((1-reflect-refractVal)*p_color).x << (refractVal*refractColor).x << endl;
               }
            }
         }
      
         else if(reflect > 0.0 && reflectDepth < 5)
         {
            //cout << norm.x << ", " << norm.y << ", " << norm.z << endl;
            //return norm;

            vec3 newD = d - 2.0f*dot(norm,d)*norm;
            vec3 p_3 = intersect + newD/2500.0f;
            //newD = vec3(m*vec4(newD, 0));
            //p_3 = vec3(m*vec4(p_3, 1));
            vec3 reflectedColor;
            if(print >= 1)
            {
               cout << "Reflected Direction " << print << " : "  << newD.x << ", " << newD.y << ", " << newD.z << endl;
               reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth, print+1, globalIll-1);
            }
            else
            {
               
               reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth, 0, globalIll-1);
            }
            if(reflectedColor != vec3(0.0,0.0,0.0))
            {
               p_color = (1-reflect)*p_color + (reflect)*reflectedColor;
            }
            //cout << "Reflect color: " << reflectedColor.x << reflectedColor.y << reflectedColor.z << endl;
            //return newD;
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

vec3 RayTracer::cosineSampleHemisphere(float u1, float u2)
{
    const float r = sqrt(u1);
    const float theta = 2 * PI * u2;
 
    const float x = r * cos(theta);
    const float y = r * sin(theta);
 
    return vec3(x, y, sqrt(std::max(0.0f, 1 - u1)));
}

float radiansToDegrees(float radians)
{
   return radians*180/PI;
}

vec3 RayTracer::hemisphereToNormalTransform(vec3 ray, vec3 normal)
{

   if(normal == vec3(0,0,1))
      return ray;
   else if(normal == vec3(0,0,-1))
      return -1.0f*ray;
   
   float theta = radiansToDegrees(acos(dot(vec3(0,0,1), normal)));
   vec3 axis = cross(vec3(0,0,1), normal);
   
   mat4 transformation = rotate(mat4(1.0f),theta, axis);
   
   vec3 transformedRay = vec3(transformation*vec4(ray,0));
   
   return transformedRay;
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

