#include "RayTracer.hpp"

RayTracer::RayTracer() {
}

RayTracer::~RayTracer() {}

double pixelToWorldX(int in_x) {
   double l = -length(cameras[0]->right)/2.0;
   double r = length(cameras[0]->right)/2.0;
   return l + (r-l)*(in_x+.5)/screenWidth;
}

double pixelToWorldY(int in_y) {
   double b = -length(cameras[0]->up)/2.0;
   double t = length(cameras[0]->up)/2.0;
   return b + (t-b)*(in_y+.5)/screenHeight;
}

void RayTracer::genRays()
{
   TGAWriter tga(screenWidth, screenHeight);
   float  u_s, v_s, w_s;
   vec3 u, v, w, p_0, p_color, d, s_prime;
   
   p_0 = cameras[0]->location;
         
   //cout << p_0.x << ", " << p_0.y << ", " << p_0.z << endl;
   
   for (int i = 0; i < screenHeight; i++)
   {
      for (int j = 0; j < screenWidth; j++)
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
         tga.colorPixel(i*(screenWidth) + j, p_color);
      }
   }
   
   tga.writeTGA(true);
}

vec3 RayTracer::raytrace(vec3 d, vec3 p_0, int reflectDepth, int refractDepth)
{
   vec3 intersect, norm, l_norm, v_norm, r_norm, p_1, p_2, shadowRay;
   float t, n_dot_l,v_dot_r, reflect, refract, refractVal;
   float* addr = &t;
   bool temp;
   double depth = DBL_MAX;
   vec3 p_color = vec3(0.0,0.0,0.0);  
    
   for(int k = 0; k < (int) geometry.size(); k++)
   {
      mat4 m_i = geometry[k]->getTransformation();
      mat4 m = inverse(m_i);
      vec3 light  = vec3(m_i*vec4(lights[0]->location,1));  //lights[0]->location;//vec3(m_i*vec4((*lights[0]).location,1));

      vec3 d_new = vec3(m_i * vec4(d,0));
      vec3 p_0_new = vec3(m_i * vec4(p_0,1));
      //cout << k << endl;
      temp = (*geometry[k]).intersect(d_new, p_0_new, addr);
      /*if (temp == true && k != 4 )
         cout << t << endl;*/
      if(temp == true && t > 0.0 && t < depth)
      {
         //cout << "in" << endl;
         depth = t;

         mat4 m_i_t = transpose(m_i);
         
         reflect = geometry[k]->fObj->reflection;
         refract = geometry[k]->fObj->refraction;
         refractVal = geometry[k]->pObj->pigment.w;
         
         intersect = vec3(p_0_new + (d_new * t));

         //geometry normal
         norm = vec3(m_i_t*vec4(normalize(geometry[k]->getNormal(intersect)), 0));

         //light vector
         l_norm = normalize(light-intersect);
         //view vector
         v_norm = normalize(-d_new);
         
         shadowRay = normalize(light - intersect); 
         // Move the intersect point slightly away so that it doesn't intersect itself
         //p_1 = intersect + shadowRay/2500.0f;
         p_1 = intersect + norm/2500.0f;
         
         shadowRay = vec3(m*vec4(shadowRay,0));
         p_1 = vec3(m*vec4(p_1,1));

         if(isShadowed(shadowRay, p_1))
         {  //set color to ambient
            p_color = vec3(geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.x*lights[0]->color.x,
                           geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.y*lights[0]->color.y, 
                           geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.z*lights[0]->color.z);
         }
         else
         {
            n_dot_l = dot(norm,l_norm);

            if(n_dot_l < 0) //clamp values between zero and 1
               n_dot_l = 0;
            else if(n_dot_l > 1.0)
               n_dot_l = 1.0;
               
            if(shadingMode == 0)  //Phong
            {
                  //reflected vector   
               r_norm = normalize(vec3(-1*l_norm.x + 2.0*n_dot_l*norm.x, -1*l_norm.y + 2.0*n_dot_l*norm.y, -1*l_norm.z + 2.0*n_dot_l*norm.z));
               v_dot_r = glm::dot(v_norm,r_norm);
                  
               if(v_dot_r < 0) //clamp values between zero and 1
                  v_dot_r = 0;
               else if(v_dot_r > 1.0)
                  v_dot_r = 1.0;
            
               v_dot_r = pow(v_dot_r, (float)(1.0/(*(*geometry[k]).fObj).roughness));
                              
               //calc color using phong    
               p_color = vec3((geometry[k]->fObj->diffuse*geometry[k]->pObj->pigment.x*n_dot_l*lights[0]->color.x + geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.x*lights[0]->color.x + geometry[k]->fObj->specular*geometry[k]->pObj->pigment.x*v_dot_r*lights[0]->color.x),
                              (geometry[k]->fObj->diffuse*geometry[k]->pObj->pigment.y*n_dot_l*lights[0]->color.y + geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.y*lights[0]->color.y + geometry[k]->fObj->specular*geometry[k]->pObj->pigment.y*v_dot_r*lights[0]->color.y), 
                              (geometry[k]->fObj->diffuse*geometry[k]->pObj->pigment.z*n_dot_l*lights[0]->color.z + geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.z*lights[0]->color.z + geometry[k]->fObj->specular*geometry[k]->pObj->pigment.z*v_dot_r*lights[0]->color.z));
            }
            else if(shadingMode == 1)             // Gaussian Distribution Specular - some code from http://www.arcsynthesis.org/gltut/Illumination/Tut11%20Gaussian.html
            {     
               //cout << "gaussian" << endl;
               vec3 halfAngle = normalize(l_norm + v_norm);
               float angleNormalHalf = acos(dot(halfAngle, norm));
               float exponent = angleNormalHalf / geometry[k]->fObj->roughness;
               exponent = -(exponent * exponent);
               float gaussianTerm = exp(exponent);
            
                p_color = vec3((geometry[k]->fObj->diffuse*geometry[k]->pObj->pigment.x*n_dot_l*lights[0]->color.x + geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.x*lights[0]->color.x + geometry[k]->fObj->specular*geometry[k]->pObj->pigment.x*gaussianTerm*lights[0]->color.x),
                              (geometry[k]->fObj->diffuse*geometry[k]->pObj->pigment.y*n_dot_l*lights[0]->color.y + geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.y*lights[0]->color.y + geometry[k]->fObj->specular*geometry[k]->pObj->pigment.y*gaussianTerm*lights[0]->color.y), 
                              (geometry[k]->fObj->diffuse*geometry[k]->pObj->pigment.z*n_dot_l*lights[0]->color.z + geometry[k]->fObj->ambient*geometry[k]->pObj->pigment.z*lights[0]->color.z + geometry[k]->fObj->specular*geometry[k]->pObj->pigment.z*gaussianTerm*lights[0]->color.z));
            }
         }
         
         if(refract > 0.0 && refractDepth < 5 && reflectDepth < 5)
         {
            vec3 refractT;
            bool success = false;
            bool* successAddr = &success;
            float cos_theta, n1, n2;
            //float R, R_0;
            

            vec3 newD = d_new - 2.0f*dot(norm,d_new)*norm;
            vec3 p_3 = intersect + newD/2500.0f;
            newD = vec3(m*vec4(newD, 0));
            p_3 = vec3(m*vec4(p_3, 1));
            vec3 reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth);
            if(reflectedColor == vec3(0.0,0.0,0.0))
            {
               reflectedColor = p_color;
            }
            
            n2 = 1;
            n1 = geometry[k]->fObj->ior;
            
            if(dot(d_new, norm) < 0)
            {
               refractT = refractRay(d_new, norm, n2, n1, successAddr);
               cos_theta = dot(d, -norm);
            }
            else
            {
               refractT = refractRay(d_new, -norm, n1, n2, successAddr);
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
               refractT = vec3(m*vec4(refractT,0));
               p_2 = vec3(m*vec4(p_2,1));
               p_color = (1-reflect-refractVal)*p_color + reflect*reflectedColor + refractVal*raytrace(refractT,p_2,reflectDepth, refractDepth+1);
            }
         }
         
         if(reflect > 0.0 && reflectDepth < 5)
         {
            vec3 newD = d_new - 2.0f*dot(norm,d_new)*norm;
            vec3 p_3 = intersect + newD/2500.0f;
            newD = vec3(m*vec4(newD, 0));
            p_3 = vec3(m*vec4(p_3, 1));
            vec3 reflectedColor = raytrace(newD,p_3,reflectDepth+1, refractDepth);
            if(reflectedColor != vec3(0.0,0.0,0.0))
            {
               p_color = (1-reflect)*p_color + (reflect)*reflectedColor;
            }
         }
      }
   }
   return p_color;
}

bool RayTracer::isShadowed(vec3 shadowRay, vec3 p_1)
{
   bool temp = false;
   float t;
   float* addr = &t;

   //cout << "shadow ray " << shadowRay.x << ", " << shadowRay.y << ", " << shadowRay.z << endl;
   //cout << p_1.x << ", " << p_1.y << ", " << p_1.z << endl;
   for(int k = 0; k < (int) geometry.size(); k++)
   {
      mat4 m_i = geometry[k]->getTransformation();
      
      vec3 d_new = vec3(m_i * vec4(shadowRay,0));
      vec3 p_0_new = vec3(m_i * vec4(p_1,1));
      
      temp = geometry[k]->intersect(d_new, p_0_new, addr);
      
      if(temp)
         return true;
   }    
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

