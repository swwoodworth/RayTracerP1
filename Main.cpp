#include "CameraObj.hpp"
#include "LightSourceObj.hpp"

#include "SphereObj.hpp"
#include "BoxObj.hpp"
#include "ConeObj.hpp"
#include "PlaneObj.hpp"
#include "TriangleObj.hpp"
#include "RayTracer.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

using namespace std;
using namespace glm;

vector<CameraObj*> cameras;
vector<LightSourceObj*> lights;
   
vector<SphereObj*> spheres;
vector<BoxObj*> boxes;
vector<ConeObj*> cones;
vector<PlaneObj*> planes;
vector<TriangleObj*> triangles;

vector<Geometry*> geometry;

int screenWidth;
int screenHeight;
int shadingMode;
int antiAliasLevel;


string fileName;

void parsePOV(ifstream &poVFile);
void printPOV();


int main(int argc, char* argv[])
{
   if (argc < 6) // Check the value of argc. If not enough parameters have been passed, inform user and exit.
   { 
        cout << "Usage: RayTracer imageWidth imageHeight -I inputFilename.pov shadingMode antiAliasLevel\n" ; // Inform the user of how to use the program
        return -1;
   }
   
   screenWidth = atoi(argv[1]);
   screenHeight = atoi(argv[2]);
   
   if ( !screenWidth ) {
      cout << "Invalid image width\n";
      cout << "Usage: RayTracer imageWidth imageHeight -I inputFilename.pov shadingMode antiAliasLevel\n" ; // Inform the user of how to use the program
      return -1;
   }
   if ( !screenHeight) {
      cout << "Invalid image height\n";
      cout << "Usage: RayTracer imageWidth imageHeight -I inputFilename.pov shadingMode antiAliasLevel\n" ; // Inform the user of how to use the program
      return -1;
   }
   if(screenHeight > 1440 || screenWidth > 1440)
   {
      cout << "Image size too large\n";
      return -1;
   }

   string tempFile = argv[4];
   fileName = tempFile.substr(0, tempFile.length() - 3) + "tga";
   cout << fileName;
   
   ifstream povFile ( argv[4] ); 
   if ( !povFile.is_open() ) 
   {
     cout << "File " << argv[4] << " could not be opened.\n";
     return -1;
   }
   
   shadingMode = atoi(argv[5]);
   if(shadingMode != 1 && shadingMode != 0)
   {
      cout << "Invalid shading mode\n";
      return -1;
   }
   
   antiAliasLevel = atoi(argv[6]);
   if(antiAliasLevel != 0 && antiAliasLevel != 4 && antiAliasLevel != 9)
   {
      cout << "Invalid anti-aliasing level\n";
      return -1;
   }
   
   parsePOV(povFile);
   //printPOV();
   RayTracer rt;
   rt.genRays();
   //cout << "I ran!\n";
   return 0;
}

void parsePOV(ifstream &povFile)
{
   string token;

   while(povFile.good()) // check if at eof
   {
      povFile >> token;

      if(token.compare("camera") == 0)
      {
         //cout << "Found Camera\n";
         CameraObj *cam = new CameraObj();
         cam->parse(povFile);
         cameras.push_back(cam);
      }
      if(token.compare("light_source") == 0)
      {
         //cout << "Found Light Source\n";
         LightSourceObj *light = new LightSourceObj();
         light->parse(povFile);
         lights.push_back(light);
      }
      if(token.compare("sphere") == 0)
      {
         //cout << "Found sphere\n";
         SphereObj *sphere = new SphereObj();
         sphere->parse(povFile);
         geometry.push_back(sphere);
      }
      if(token.compare("box") == 0)
      {
         //cout << "Found box\n";
         BoxObj *box = new BoxObj();
         box->parse(povFile);
         geometry.push_back(box);
      } 
      if(token.compare("cone") == 0)
      {
         //cout << "Found cone\n";
         ConeObj *cone = new ConeObj();
         cone->parse(povFile);
         geometry.push_back(cone);
      } 
      if(token.compare("plane") == 0)
      {
         //cout << "Found plane\n";
         PlaneObj *plane = new PlaneObj();
         plane->parse(povFile);
         geometry.push_back(plane);
      } 
      if(token.compare("triangle") == 0)
      {
         //cout << "Found triangle\n";
         TriangleObj *triangle = new TriangleObj();
         triangle->parse(povFile);
         geometry.push_back(triangle);
      } 
      if(token.compare("//") == 0)
      {
         getline(povFile, token);  //swallow comment line
         //cout << token;
      } 
      //cout << token << endl;
      token = "";
   }
}

void printPOV()
{
   for(unsigned int i = 0; i<cameras.size(); i++)
   {
      cout << "Camera: " << *cameras[i] << endl;
   }
   
   for(unsigned int i = 0; i<lights.size(); i++)
   {
      cout << "Light: " << *lights[i] << endl;
   }
   
   for(unsigned int i = 0; i<spheres.size(); i++)
   {
      cout << "Sphere: " << *spheres[i] << endl;
   }
   
   for(unsigned int i = 0; i<boxes.size(); i++)
   {
      cout << "Box: " << *boxes[i] << endl;
   }
   
   for(unsigned int i = 0; i<cones.size(); i++)
   {
      cout << "Cone: " << *cones[i] << endl;
   }
   
   for(unsigned int i = 0; i<planes.size(); i++)
   {
      cout << "Plane: " << *planes[i] << endl;
   }
   
   for(unsigned int i = 0; i<triangles.size(); i++)
   {
      cout << "Triangle: " << *triangles[i] << endl;
   }
   
   for(unsigned int i = 0; i<geometry.size(); i++)
   {
      //cout << *geometry[i] << endl;
   }
}