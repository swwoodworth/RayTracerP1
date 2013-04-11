#include "TGAWriter.hpp"

TGAWriter::TGAWriter() {
}

TGAWriter::~TGAWriter() {}

void TGAWriter::writeTGA(Pixel *pixels, int screenHeight, int screenWidth) {
   // tga
   FILE *fp;
   //int x, y;
   fp = fopen("output.tga", "w");
   if (!fp)
   {
      printf("tga file could not be written\n");
      exit(EXIT_FAILURE);
   }

   //Write Header
   fputc(0,fp);
   fputc(0,fp);

   // uncompressed RGB 
   fputc(2,fp);                         
   fputc(0,fp); 
   fputc(0,fp);
   fputc(0,fp); 
   fputc(0,fp);
   fputc(0,fp);

   // X origin 
   fputc(0,fp); 
   fputc(0,fp);           
   // y origin 
   fputc(0,fp); 
   fputc(0,fp);

   // width and height        
   fputc((screenWidth & 0x00FF),fp);
   fputc((screenWidth & 0xFF00) >> 8,fp);
   fputc((screenHeight & 0x00FF),fp);
   fputc((screenHeight & 0xFF00) >> 8,fp);

   // 24 bit bitmap 
   fputc(24,fp);                        
   fputc(0,fp);

   //Write Data
   int size = screenHeight * screenWidth;
   for (int i = 0; i < size; i++)
   {
      fputc(((unsigned char)pixels[i].r),fp);
      fputc(((unsigned char)pixels[i].g),fp);
      fputc(((unsigned char)pixels[i].b),fp);
   }

   fclose(fp);
}