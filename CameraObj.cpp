#include "CameraObj.hpp"

CameraObj::CameraObj() {
   ObjID = -1;
}

CameraObj::CameraObj(int id) {
   ObjID = id;
}

CameraObj::~CameraObj() {}

ostream& operator<< (ostream &out, CameraObj &cObj)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << cObj.location.x << ", " <<
                  cObj.location.y << ", " <<
                  cObj.location.z << ")";
    return out;
}


void CameraObj::parse(ifstream &povFile) {
   string token;
   string line;
   char *line2;
   //char *token2;
   
   cout << "I'm parsing a camera" << endl;
   
   while(povFile.good()) // check if at eof
   {
      povFile >> token;

      if(token.compare("}") == 0)
      {
         //cout << "end a sphere" << endl;
         return; // found end of camera information
      }    
      else if(token.compare("location") == 0)
      {
         getline(povFile, line);
         line2 = (char*)line.c_str();
         location.x = atof(strtok (line2," <,>"));
         location.y = atof(strtok (NULL," <,>"));
         location.z = atof(strtok (NULL," <,>")); 
      }
      else if(token.compare("up") == 0)
      {
         getline(povFile, line);
         line2 = (char*)line.c_str();
         up.x = atof(strtok (line2," <,>"));
         up.y = atof(strtok (NULL," <,>"));
         up.z = atof(strtok (NULL," <,>")); 
      }
      else if(token.compare("right") == 0)
      {
         getline(povFile, line);
         line2 = (char*)line.c_str();
         right.x = atof(strtok (line2," <,>"));
         right.y = atof(strtok (NULL," <,>"));
         right.z = atof(strtok (NULL," <,>")); 
      }
      else if(token.compare("look_at") == 0)
      {
         getline(povFile, line);
         line2 = (char*)line.c_str();
         lookAt.x = atof(strtok (line2," <,>"));
         lookAt.y = atof(strtok (NULL," <,>"));
         lookAt.z = atof(strtok (NULL," <,>")); 
      }
   }
}
