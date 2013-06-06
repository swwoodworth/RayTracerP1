#include "ShadingModel.hpp"
#include "Perlin.hpp"

ShadingModel::ShadingModel() {
}

ShadingModel::~ShadingModel() {}

vec3 ShadingModel::phong(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient) {   
   
   
   vec4 pigment;
   if (geom->perlin == false)
      pigment = geom->pObj->pigment;
   else
   {
      float p = noise(intersect.x, intersect.y, intersect.z)/2;
      cout << p << endl;
      pigment = vec4(p*geom->pObj->pigment.x,p*geom->pObj->pigment.y,p*geom->pObj->pigment.z,1);
   }

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
                           
   return vec3((geom->fObj->diffuse*pigment.x*n_dot_l*lights[l]->color.x + ambient.x + geom->fObj->specular*pigment.x*v_dot_r*lights[l]->color.x),
               (geom->fObj->diffuse*pigment.y*n_dot_l*lights[l]->color.y + ambient.y + geom->fObj->specular*pigment.y*v_dot_r*lights[l]->color.y), 
               (geom->fObj->diffuse*pigment.z*n_dot_l*lights[l]->color.z + ambient.z + geom->fObj->specular*pigment.z*v_dot_r*lights[l]->color.z));
}

vec3 ShadingModel::gaussian(vec3 intersect, vec3 norm, vec3 l_norm, vec3 v_norm, Geometry *geom, int l, vec3 ambient) {   
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
   
   return vec3((geom->fObj->diffuse*geom->pObj->pigment.x*n_dot_l*lights[l]->color.x + ambient.x + geom->fObj->specular*geom->pObj->pigment.x*gaussianTerm*lights[l]->color.x),
               (geom->fObj->diffuse*geom->pObj->pigment.y*n_dot_l*lights[l]->color.y + ambient.y + geom->fObj->specular*geom->pObj->pigment.y*gaussianTerm*lights[l]->color.y), 
               (geom->fObj->diffuse*geom->pObj->pigment.z*n_dot_l*lights[l]->color.z + ambient.z + geom->fObj->specular*geom->pObj->pigment.z*gaussianTerm*lights[l]->color.z));
}
