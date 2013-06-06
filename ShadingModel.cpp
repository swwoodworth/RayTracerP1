#include "ShadingModel.hpp"
#include "Perlin.hpp"

ShadingModel::ShadingModel() {
}

ShadingModel::~ShadingModel() {}

vec3 ShadingModel::phong(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient) {   
   
   
   vec4 pigment = getPigment(geom, intersect);
   
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
 
   vec4 pigment = getPigment(geom, intersect);
   
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

vec4 ShadingModel::getPigment(Geometry *geom, vec3 intersect)
{
   if (geom->perlin == false)
      return geom->pObj->pigment;
   else
   {
      float p = noise(intersect.x*2, intersect.y*2, intersect.z*2)/3;
      //cout << p << endl;
      return p*geom->pObj->pigment;
   }
}
