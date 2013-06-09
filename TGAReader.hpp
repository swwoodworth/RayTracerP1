#ifndef TGAR_H
#define TGAR_H

#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>

#include "Pixel.hpp"

using namespace std;

typedef struct {
   char  idlength;
   char  colourmaptype;
   char  datatypecode;
   short int colourmaporigin;
   short int colourmaplength;
   char  colourmapdepth;
   short int x_origin;
   short int y_origin;
   short width;
   short height;
   char  bitsperpixel;
   char  imagedescriptor;
} Header;


class TGAReader {
   public:
      TGAReader(); //default constructor
      ~TGAReader(); //destructor
      Pixel* TGARead(string path, int *texWidth, int *texHeight);
      bool readHeader(FILE *fp, Header *header);
      void printError(string error);
      void printHeader(Header *header);

};

#endif