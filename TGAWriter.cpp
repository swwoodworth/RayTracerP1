#include "TGAWriter.hpp"

TGAWriter::TGAWriter() {
}

TGAWriter::~TGAWriter() {}

void TGAWriter::writeTGA(Pixel *pixels, int screenWidth, int screenHeight) {
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
   fputc((screenWidth & 0xFF00) / 256,fp);
   fputc((screenHeight & 0x00FF),fp);
   fputc((screenHeight & 0xFF00) / 256,fp);

   // 24 bit bitmap 
   fputc(24,fp);                        
   fputc(0,fp);

   //Write Data
   for (int i = 0; i < screenHeight; i++)
   {
      for (int j = 0; j < screenWidth; j++)
      {
         //if(pixels[i*(screenWidth) + j].r != 0)
         //   cout << pixels[i*(screenWidth) + j].r << endl;
         //else 
         //   cout << "-";
         fputc((char)((pixels[i*(screenWidth) + j].b)*255),fp);
         fputc((char)((pixels[i*(screenWidth) + j].g)*255),fp);
         fputc((char)((pixels[i*(screenWidth) + j].r)*255),fp);
      }
      //cout << "\n";
      
   }

   fclose(fp);
}