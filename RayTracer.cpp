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
   float  u_s, v_s, w_s;
   vec3 u, v, w, p_0;
   double t, depth;
   vec3 d, s_prime;
   
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
         
         d = s_prime - p_0;
         
         /*for(int s = 0; s < (int) spheres.size(); s++)
         {
            t = (*spheres[s]).intersect(d, p_0);
            if(t > 0.0 && t < depth)
            {
               depth = t;
               pixels[i*(screenWidth) + j].r = (*(*spheres[s]).pObj).pigment.x;
               pixels[i*(screenWidth) + j].g = (*(*spheres[s]).pObj).pigment.y;
               pixels[i*(screenWidth) + j].b = (*(*spheres[s]).pObj).pigment.z;
               //cout << "color " << (*(*spheres[s]).pObj).pigment.x << ", " << (*(*spheres[s]).pObj).pigment.y << ", " << (*(*spheres[s]).pObj).pigment.z << endl;
            }
         }
         
         for(int p = 0; p < (int) planes.size(); p++)
         {
            t = (*planes[p]).intersect(d, p_0);
            //cout << t << endl;
            if(t > 0.0 && t < depth)
            {
               
               depth = t;
               pixels[i*(screenWidth) + j].r = (*(*planes[p]).pObj).pigment.x;
               pixels[i*(screenWidth) + j].g = (*(*planes[p]).pObj).pigment.y;
               pixels[i*(screenWidth) + j].b = (*(*planes[p]).pObj).pigment.z;
               //cout << "color " << (*(*planes[p]).pObj).pigment.x << ", " << (*(*planes[p]).pObj).pigment.y << ", " << (*(*planes[p]).pObj).pigment.z << endl;
            }
         }*/
         
         for(int k = 0; k < (int) geometry.size(); k++)
         {
            t = (*geometry[k]).intersect(d, p_0);
            //cout << t << endl;
            if(t > 0.0 && t < depth)
            {
               
               depth = t;
               pixels[i*(screenWidth) + j].r = (*(*geometry[k]).pObj).pigment.x;
               pixels[i*(screenWidth) + j].g = (*(*geometry[k]).pObj).pigment.y;
               pixels[i*(screenWidth) + j].b = (*(*geometry[k]).pObj).pigment.z;
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