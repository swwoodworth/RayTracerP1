#include "ShadingModel.hpp"
#include "Perlin.hpp"

ShadingModel::ShadingModel() {
}

ShadingModel::~ShadingModel() {}

vec3 ShadingModel::phong(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient) {   
   
   
   vec4 pigment = getPigment(geom, intersect, norm);
   
   if (geom->perlinNormal == true)
      norm *= (float)noise(intersect.x, intersect.y, intersect.z)/2;

   float n_dot_l = dot(norm,l_norm);
   //cout << n_dot_l << endl;

   if(n_dot_l < 0) //clamp values between zero and 1
      n_dot_l = 0;
   else if(n_dot_l > 1.0)
      n_dot_l = 1.0;
            
 
   //reflected vector   
   vec3 r_norm = normalize(-1.0f*l_norm + 2.0f*n_dot_l*norm);
   float v_dot_r = glm::dot(v_norm,r_norm);
               
   if(v_dot_r < 0) //clamp values between zero and 1
      v_dot_r = 0;
   else if(v_dot_r > 1.0)
      v_dot_r = 1.0;
         
   v_dot_r = pow(v_dot_r, (float)(1.0/geom->fObj->roughness));
   //cout << v_dot_r << endl;
                           
   return (geom->fObj->diffuse*vec3(pigment)*n_dot_l*lights[l]->color + ambient + geom->fObj->specular*vec3(pigment)*v_dot_r*lights[l]->color);
}

vec3 ShadingModel::gaussian(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient) { 
 
   vec4 pigment = getPigment(geom, intersect, norm);
   
   if (geom->perlinNormal == true)
      norm *= (float)noise(intersect.x, intersect.y, intersect.z)/2;
 
   float n_dot_l = dot(norm,l_norm);
   //cout << n_dot_l << endl;

   if(n_dot_l < 0) //clamp values between zero and 1
      n_dot_l = 0;
   else if(n_dot_l > 1.0)
      n_dot_l = 1.0;
            
 
   //cout << "gaussian" << endl;
   vec3 halfAngle = normalize(l_norm + v_norm);
   float angleNormalHalf = acos(dot(halfAngle, norm));
   float exponent = angleNormalHalf / geom->fObj->roughness;
   exponent = -(exponent * exponent);
   float gaussianTerm = exp(exponent);
   
   return (geom->fObj->diffuse*vec3(pigment)*n_dot_l*lights[l]->color + ambient + geom->fObj->specular*vec3(pigment)*gaussianTerm*lights[l]->color);
}

vec4 ShadingModel::getPigment(Geometry *geom, vec3 intersect, vec3 norm)
{
   if (geom->perlin == true)
   {
      float p = noise(intersect.x*2, intersect.y*2, intersect.z*2)/3;
      //cout << p << endl;
      return p*geom->pObj->pigment;
   }
   else if (geom->texture.compare("") != 0)
   {    
      float u = asin(norm.x)/PI + 0.5;
      //u = norm.x/2 + 0.5;
      float v = asin(norm.y)/PI + 0.5;
      //v = norm.y/2 + 0.5;

      int width = 0;
      int height = 0;
      Pixel *pixels;
      for(int i = 0; i < (int)textures.size(); i++)
      {
         if(textures[i]->name.compare(geom->texture) == 0)
         {
            width = (int)textures[i]->texWidth;
            height = (int)textures[i]->texHeight;
            //cout << width << " " << height << endl;
            pixels = textures[i]->pixels;
         }
      }
   
      float u_prime = width*u - floor(width*u);
      float v_prime = height*v - floor(height*v);
   
      float u_double_prime = 3*pow(u_prime,2) - 2*pow(u_prime,3);
      float v_double_prime = 3*pow(v_prime,2) - 2*pow(v_prime,3);

      //tga.colorPixel(i*(screenWidth) + j, p_color);
      int i =  (int)floor(u*width);
      int j = (int)floor(v*height);
   
      vec3 ci1j;
      vec3 cij1;
      vec3 ci1j1;
   
      vec3 cij = vec3(pixels[j*width + i].r, pixels[j*width + i].g, pixels[j*width + i].b);
      if(i == width)
         ci1j = vec3(pixels[j*width].r, pixels[j*width-1].g, pixels[j*width].b);
      else
         ci1j = vec3(pixels[j*width + i+1].r, pixels[j*width + i+1].g, pixels[j*width + i+1].b);
      if(j == height)
         cij1 = vec3(pixels[i].r, pixels[i].g, pixels[i].b);
      else
         cij1 = vec3(pixels[(j)*width + i].r, pixels[(j+1)*width + i].g, pixels[(j)*width + i].b);
      if(i == width && j == height)
         ci1j1 = vec3(pixels[0].r, pixels[0].g, pixels[0].b);
      else if (i == width)
         ci1j1 = vec3(pixels[(j)*width].r, pixels[(j+1)*width].g, pixels[(j+1)*width].b);
      else if(j == height)
         ci1j1 = vec3(pixels[i + 1].r, pixels[i + 1].g, pixels[i + 1].b);
      else
         ci1j1 = vec3(pixels[(j+1)*width + i + 1].r, pixels[(j+1)*width + i + 1].g, pixels[(j+1)*width + i + 1].b);;

      vec4 color = vec4(((1-u_double_prime)*(1-v_double_prime)*cij + 
             u_double_prime*(1-v_double_prime)*ci1j +
             (1-u_double_prime)*v_double_prime*cij1 +
             u_double_prime*v_double_prime*ci1j1)/255.0f,1);
      //color = vec4(cij,1);
      //cout << color.x << " " <<color.y << " " << color.z << endl;
      return color;
   }
   else
   {
      return geom->pObj->pigment;
   }
}
