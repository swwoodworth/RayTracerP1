#include "RayTracer.hpp"

RayTracer::RayTracer() {
}

RayTracer::~RayTracer() {}

double pixelToWorldX(int in_x) {
   double l = -length((*cameras[0]).right)/2.0;
   double r = length((*cameras[0]).right)/2.0;
   return l + (r-l)*(in_x+.5)/screenWidth;
}

double pixelToWorldY(int in_y) {
   double b = -length((*cameras[0]).up)/2.0;
   double t = length((*cameras[0]).up)/2.0;
   return b + (t-b)*(in_y+.5)/screenHeight;
}

void RayTracer::trace()
{
   TGAWriter tga(screenWidth, screenHeight);
   float  u_s, v_s, w_s, t, n_dot_l,v_dot_r;
   vec3 u, v, w, p_0, p_1, intersect, shadowRay, norm, l_norm, v_norm, r_norm, p_color;
   double depth;
   vec3 d, s_prime;
   bool temp;
   float* addr = &t;
   
   p_0 = (*cameras[0]).location;
         
   //cout << p_0.x << ", " << p_0.y << ", " << p_0.z << endl;
   
   for (int i = 0; i < screenHeight; i++)
   {
      for (int j = 0; j < screenWidth; j++)
      {
         p_color = vec3(0.0,0.0,0.0);
         depth = DBL_MAX;
         
         u_s = pixelToWorldX(j);
         v_s = pixelToWorldY(i);
         w_s = -1;
         //cout << i_x << ", " << i_y << endl;
         u = (*cameras[0]).right/ length((*cameras[0]).right);
         v = (*cameras[0]).up/ length((*cameras[0]).up);
         w =  cross(u, v);
         
         s_prime = p_0 + u_s*u + v_s*v + w_s*w;
         
         d = normalize(s_prime - p_0);
         
         for(int k = 0; k < (int) geometry.size(); k++)
         {
            temp = (*geometry[k]).intersect(d, p_0, addr);
            //cout << t << endl;
            if(temp == true && t > 0.0 && t < depth)
            {
               
               depth = t;
               intersect = vec3(p_0 + (d * t));
               
               //geometry normal
               norm = (*geometry[k]).getNormal(intersect);
               //normalized light vector
               l_norm = normalize(vec3((*lights[0]).location-intersect));
               //view vector
               v_norm = normalize(-d);
               
               // Move the intersect point slightly away from sphere so that it doesn't intersect itself
               p_1 = vec3((intersect.x + norm.x/25), (intersect.y + norm.y/25), (intersect.z + norm.z/25));
               
               shadowRay = normalize((*lights[0]).location - p_1); 
               if(isShadowed(shadowRay, p_1))
               {  //set color to ambient
                  p_color = vec3((*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.x*(*lights[0]).color.x,
                                 (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.y*(*lights[0]).color.y, 
                                 (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.z*(*lights[0]).color.z);
               }
               else
               {
                  n_dot_l = dot(norm,l_norm);
   
                  if(n_dot_l < 0) //clamp values between zero and 1
                     n_dot_l = 0;
                  else if(n_dot_l > 1.0)
                     n_dot_l = 1.0;
                     
                  //reflected vector   
                  r_norm = normalize(vec3(-1*l_norm.x + 2.0*n_dot_l*norm.x, -1*l_norm.y + 2.0*n_dot_l*norm.y, -1*l_norm.z + 2.0*n_dot_l*norm.z));
                  v_dot_r = glm::dot(v_norm,r_norm);
                        
                  if(v_dot_r < 0) //clamp values between zero and 1
                     v_dot_r = 0;
                  else if(v_dot_r > 1.0)
                     v_dot_r = 1.0;
                  
                  v_dot_r = pow(v_dot_r, (float)(1.0/(*(*geometry[k]).fObj).roughness));
                                    
                  //calc color using phong    
                  p_color = vec3(((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.x*n_dot_l*(*lights[0]).color.x + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.x*(*lights[0]).color.x + (*(*geometry[k]).fObj).specular*(*(*geometry[k]).pObj).pigment.x*v_dot_r*(*lights[0]).color.x),
                                 ((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.y*n_dot_l*(*lights[0]).color.y + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.y*(*lights[0]).color.y + (*(*geometry[k]).fObj).specular*(*(*geometry[k]).pObj).pigment.y*v_dot_r*(*lights[0]).color.y), 
                                 ((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.z*n_dot_l*(*lights[0]).color.z + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.z*(*lights[0]).color.z + (*(*geometry[k]).fObj).specular*(*(*geometry[k]).pObj).pigment.z*v_dot_r*(*lights[0]).color.z)); 
               }
            }
         }
         tga.colorPixel(i*(screenWidth) + j, p_color);
      }
   }
   
   tga.writeTGA(true);
}

bool RayTracer::isShadowed(vec3 shadowRay, vec3 p_1)
{
   bool temp;
   float t;
   float* addr = &t;

   //cout << "shadow ray " << shadowRay.x << ", " << shadowRay.y << ", " << shadowRay.z << endl;
   //cout << p_1.x << ", " << p_1.y << ", " << p_1.z << endl;
   
   for(int k = 0; k < (int) geometry.size(); k++)
   {
      temp = (*geometry[k]).intersect(shadowRay, p_1, addr); 
      if(temp)
         return true;
   }    
   return false;       
}

