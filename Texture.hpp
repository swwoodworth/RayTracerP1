#ifndef TEX_H
#define TEX_H

#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>

#include "Pixel.hpp"
#include "TGAReader.hpp"

using namespace std;

class Texture {
   public:
      Texture(); //default constructor
      ~Texture(); //destructor
      void parse(ifstream &povFile);

      string name;
      Pixel *pixels;
      int texWidth;
      int texHeight;
};

#endif