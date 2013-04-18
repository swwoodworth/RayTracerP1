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
   Pixel *pixels = (Pixel*)calloc(screenWidth * screenHeight, sizeof(Pixel));
   float  u_s, v_s, w_s, t, n_dot_l,v_dot_r;
   vec3 u, v, w, p_0, intersect, norm, l_norm, v_norm, r_norm, p_color;
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
               
               //cout << (*(*geometry[k]).fObj).roughness << endl;
                     
               //calc color using phong    
               p_color = vec3(((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.x*n_dot_l*(*lights[0]).color.x + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.x*(*lights[0]).color.x + (*(*geometry[k]).fObj).specular*(*(*geometry[k]).pObj).pigment.x*v_dot_r*(*lights[0]).color.x),
                              ((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.y*n_dot_l*(*lights[0]).color.y + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.y*(*lights[0]).color.y + (*(*geometry[k]).fObj).specular*(*(*geometry[k]).pObj).pigment.y*v_dot_r*(*lights[0]).color.y), 
                              ((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.z*n_dot_l*(*lights[0]).color.z + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.z*(*lights[0]).color.z + (*(*geometry[k]).fObj).specular*(*(*geometry[k]).pObj).pigment.z*v_dot_r*(*lights[0]).color.z)); 
               
               /*p_color = vec3((*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.x*(*lights[0]).color.x,
                              (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.y*(*lights[0]).color.y, 
                              (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.z*(*lights[0]).color.z);
                              
               p_color = vec3((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.x*n_dot_l*(*lights[0]).color.x,
                              (*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.y*n_dot_l*(*lights[0]).color.y, 
                              (*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.z*n_dot_l*(*lights[0]).color.z);  
                              
               p_color = vec3(((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.x*n_dot_l*(*lights[0]).color.x + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.x*(*lights[0]).color.x),
                              ((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.y*n_dot_l*(*lights[0]).color.y + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.y*(*lights[0]).color.y), 
                              ((*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.z*n_dot_l*(*lights[0]).color.z + (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.z*(*lights[0]).color.z)); */
                              
               /*pixels[i*(screenWidth) + j].r = (*(*geometry[k]).pObj).pigment.x;
               pixels[i*(screenWidth) + j].g = (*(*geometry[k]).pObj).pigment.y;
               pixels[i*(screenWidth) + j].b = (*(*geometry[k]).pObj).pigment.z;*/
               
               pixels[i*(screenWidth) + j].r = p_color.x;
               pixels[i*(screenWidth) + j].g = p_color.y;
               pixels[i*(screenWidth) + j].b = p_color.z;
               if (p_color.x > 1.0 || p_color.z > 1.0 || p_color.z > 1.0)
                  cout << "x ambient (" << (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.x*(*lights[0]).color.x << ", " << (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.y*(*lights[0]).color.y << ", " << (*(*geometry[k]).fObj).ambient*(*(*geometry[k]).pObj).pigment.z*(*lights[0]).color.z 
                       << ")\n  diffuse (" << (*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.x*n_dot_l*(*lights[0]).color.x << ", " << (*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.y*n_dot_l*(*lights[0]).color.y << ", " << (*(*geometry[k]).fObj).diffuse*(*(*geometry[k]).pObj).pigment.z*n_dot_l*(*lights[0]).color.z
                       << ")\n";
               
               //cout << p_color.x << ", " << p_color.y << ", " << p_color.z << endl;
               
               /*pixels[i*(screenWidth) + j].r = v_norm.x;
               pixels[i*(screenWidth) + j].g = v_norm.y;
               pixels[i*(screenWidth) + j].b = v_norm.z;*/
               
               //cout << "color " << (*(*planes[p]).pObj).pigment.x << ", " << (*(*planes[p]).pObj).pigment.y << ", " << (*(*planes[p]).pObj).pigment.z << endl;
            }
         }
         
         /*if (pixels[i*(screenWidth) + j].r == 0)
         {
            cout << "-";
         }
         else
            cout << "+";*/
         //d = vec3(i_x, i_y, (*cameras[0]).location.z+1) - (*cameras[0]).location;
         //cout << d.x << ", " << d.y << ", " << d.z << endl;
      }
      //cout << "\n";
   }
   
   
   TGAWriter tga;
   tga.writeTGA(pixels, screenWidth, screenHeight);
   free(pixels);
}