#include "Geometry.hpp"

Geometry::Geometry() {
   ObjID = -1;
   m = mat4(1.0f);
   m_i = mat4(1.0f);
   perlin = false;
   perlinNormal = false;
   texture = "";
}

Geometry::Geometry(int id) {
   ObjID = id;
   m = mat4(1.0f);
   m_i = mat4(1.0f);
   perlin = false;
   perlinNormal = false;
   texture = "";
}

Geometry::~Geometry() {}

// print out matrix by rows
void printMat(glm::mat4  mat){
  int i,j;
  for (j=0; j<4; j++){
    for (i=0; i<4; i++){
    printf("%f ",mat[i][j]);
  }
  printf("\n");
 }
}

void Geometry::parseGeometry(ifstream &povFile) {
   string token;
   
   while(povFile.good()) // check if at eof
   {
      povFile >> token;

      if(token.compare("}") == 0)
      { 
         m_i = glm::inverse(m);
         //printMat(m);
         //cout << endl;
         return; // found end of parameters
      }
      else if(token.compare("pigment") == 0)
      {
         pObj = new PigmentObj();
         pObj->parse(povFile);
      }
      else if(token.compare("finish") == 0)
      {
         fObj = new FinishObj();
         fObj->parse(povFile);
      }
      else if(token.compare("translate") == 0)
      {
         tObj = new TranslateObj();
         tObj->parse(povFile);
         m = (tObj->getTranslate()) * m;
      }
      else if(token.compare("scale") == 0)
      {
         sObj = new ScaleObj();
         sObj->parse(povFile);
         m = (sObj->getScale()) * m;
      }
      else if(token.compare("rotate") == 0)
      {
         rObj = new RotateObj();
         rObj->parse(povFile);
         m = (rObj->getRotate()) * m;
      }
      else if(token.compare("perlin") == 0)
      {
         perlin = true;
      }
      else if(token.compare("perlinNormal") == 0)
      {
         perlinNormal = true;
      }
      else if(token.compare("texture") == 0)
      {
         Texture *newTexture = new Texture();
         newTexture->parse(povFile);
         texture = newTexture->name;
         bool newTex = true;
         for(int i = 0; i < (int)textures.size(); i++)
         {
            if(textures[i]->name == texture)   // check if texture already exists
               newTex = false;
         }
         if(newTex == true)
            textures.push_back(newTexture);
      }
   }
}

mat4 Geometry::getTransformation() {
   /*cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << endl;
   cout << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << endl;
   cout << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << endl;
   cout << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << endl << endl;*/
   return m_i;
}

