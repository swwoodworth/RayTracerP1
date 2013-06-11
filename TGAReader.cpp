#include "TGAReader.hpp"

TGAReader::TGAReader() {
}

TGAReader::~TGAReader() {
}

Pixel* TGAReader::TGARead(string path, int *texWidth, int *texHeight)
{
   FILE *fp;
   Pixel *pixels;
   Header header;
   Header *hp = &header;
   int n = 0;
   int i;
   unsigned char p[5];


   //unsigned char rbyte, gbyte, bbyte;
   char* fileName = (char*)path.c_str();
   fileName  = strtok (fileName,"{ <,>}");
   //cout << fileName << endl;
   /* Open the file */
   if ((fp = fopen(fileName,"r")) == NULL) {
      fprintf(stderr,"File open failed\n");
      exit(-1);
   }
   
   readHeader(fp, hp);
   
   *texWidth = header.width;
   *texHeight = header.height;
   /* Allocate space for the image */
   if ((pixels = (Pixel*)malloc(header.width*header.height*sizeof(Pixel))) == NULL) 
   {
      fprintf(stderr,"malloc of image failed\n");
      exit(-1);
   }
   for (i=0;i<header.width*header.height;i++) 
   {
      pixels[i].r = 0;
      pixels[i].g = 0;
      pixels[i].b = 0;
   }
   
   /* Skip over unnecessary stuff */
   int skipover = header.idlength;
   skipover += header.colourmaptype * header.colourmaplength;
   //fprintf(stderr,"Skip over %d bytes\n",skipover);
   fseek(fp,skipover,SEEK_CUR);
   
   /* Read the image */
   unsigned int bytes2read = header.bitsperpixel / 8;
   while (n < header.width * header.height) {
      if (header.datatypecode == 2)      /* Uncompressed */
      {                     
         if (fread(p,1,bytes2read,fp) != bytes2read) 
         {
            fprintf(stderr,"Unexpected end of file\n");
            exit(-1);
         }
         pixels[n].r = p[2];
         pixels[n].g = p[1];
         pixels[n].b = p[0];
         n++;
      }
   } 

   fclose(fp);
   return pixels;
}


bool TGAReader::readHeader(FILE *fp, Header *header)
{
   header->idlength = fgetc(fp);
   //fprintf(stderr,"ID length:         %d\n",header->idlength);
   if(header->idlength != 0)
      printError("Invalid TGA header ID length");
      
   header->colourmaptype = fgetc(fp);
   //fprintf(stderr,"Colourmap type:    %d\n",header->colourmaptype);
   if(header->colourmaptype != 0)
      printError("Invalid TGA header color map type");
      
   header->datatypecode = fgetc(fp);
   //fprintf(stderr,"Image type:        %d\n",header->datatypecode);
   if(header->datatypecode != 2)
      printError("Invalid TGA header data type code");
      
   fread(&header->colourmaporigin,2,1,fp);
   //fprintf(stderr,"Colour map offset: %d\n",header->colourmaporigin);
   if(header->colourmaporigin != 0)
      printError("Invalid TGA header colour map origin");
      
   fread(&header->colourmaplength,2,1,fp);
   //fprintf(stderr,"Colour map length: %d\n",header->colourmaplength); 
   
      
   header->colourmapdepth = fgetc(fp);
   //fprintf(stderr,"Colour map depth:  %d\n",header->colourmapdepth);
   if(header->colourmapdepth != 0)
      printError("Invalid TGA header colour map depth");
      
   fread(&header->x_origin,2,1,fp);
   //fprintf(stderr,"X origin:          %d\n",header->x_origin);
   if(header->x_origin != 0)
      printError("Invalid TGA header x origin");
      
   fread(&header->y_origin,2,1,fp);
   //fprintf(stderr,"Y origin:          %d\n",header->y_origin);
   if(header->y_origin != 0)
      printError("Invalid TGA header y origin");
      
   fread(&header->width,2,1,fp);
   //fprintf(stderr,"Width:             %d\n",header->width);
   if(header->width <= 0)
      printError("Invalid TGA header width");
      
   fread(&header->height,2,1,fp);
   //fprintf(stderr,"Height:            %d\n",header->height);
   if(header->height <= 0)
      printError("Invalid TGA header height");
      
   header->bitsperpixel = fgetc(fp);
   //fprintf(stderr,"Bits per pixel:    %d\n",header->bitsperpixel);
   if(header->bitsperpixel != 24)
      printError("Invalid TGA header bits per pixel");
   
   header->imagedescriptor = fgetc(fp);
   //fprintf(stderr,"Descriptor:        %d\n",header->imagedescriptor);
   if(header->imagedescriptor != 0)
      printError("Invalid TGA header image descriptor");
      
   return true;
}

void TGAReader::printError(string error)
{
   cout << error;
   exit(EXIT_FAILURE);
}

void TGAReader::printHeader(Header *header)
{
   fprintf(stderr,"ID length:         %d\n",header->idlength);
   fprintf(stderr,"Colourmap type:    %d\n",header->colourmaptype);
   fprintf(stderr,"Image type:        %d\n",header->datatypecode);
   fprintf(stderr,"Colour map offset: %d\n",header->colourmaporigin);
   fprintf(stderr,"Colour map length: %d\n",header->colourmaplength); 
   fprintf(stderr,"Colour map depth:  %d\n",header->colourmapdepth);
   fprintf(stderr,"X origin:          %d\n",header->x_origin);
   fprintf(stderr,"Y origin:          %d\n",header->y_origin);
   fprintf(stderr,"Width:             %d\n",header->width);
   fprintf(stderr,"Height:            %d\n",header->height);
   fprintf(stderr,"Bits per pixel:    %d\n",header->bitsperpixel);
   fprintf(stderr,"Descriptor:        %d\n",header->imagedescriptor);
}
