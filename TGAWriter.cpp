#include "TGAWriter.hpp"

TGAWriter::TGAWriter(int width, int height) {
   screenWidth = width;
   screenHeight = height;
   pixels = (Pixel*)calloc(screenWidth * screenHeight, sizeof(Pixel));
}

TGAWriter::~TGAWriter() {
   free(pixels);
}

void TGAWriter::colorPixel(int pixel, vec3 color)
{
   if (pixel < 0 || pixel > screenWidth*screenHeight)
   {
      // catostrophically fail
      fprintf(stderr, "ERROR: pixel outside range of the image!\n");
      exit(EXIT_FAILURE);
   }
    
   pixels[pixel].r = color.x;
   pixels[pixel].g = color.y;
   pixels[pixel].b = color.z;

   // update the max color if necessary
   if(color.x > max)
      max = color.x;
   if(color.y > max)
       max = color.y;
   if(color.z > max)
       max = color.z;
}

void TGAWriter::writeTGA(bool scale) {
   // tga
   FILE *fp;
   unsigned char rbyte, gbyte, bbyte;

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
         if (scale)
         {
            rbyte = (unsigned char)((pixels[i*(screenWidth) + j].r / max) * 255);
            gbyte = (unsigned char)((pixels[i*(screenWidth) + j].g / max) * 255);
            bbyte = (unsigned char)((pixels[i*(screenWidth) + j].b / max) * 255);
         }
         else
         {
            if(pixels[i*(screenWidth) + j].r > 1.0)
               rbyte = (unsigned char)(255);
            else
               rbyte = (unsigned char)(pixels[i*(screenWidth) + j].r*255);
               
            if(pixels[i*(screenWidth) + j].g > 1.0)
               gbyte = (unsigned char)(255);
            else
               gbyte = (unsigned char)(pixels[i*(screenWidth) + j].g*255);
               
            if(pixels[i*(screenWidth) + j].b > 1.0)
               bbyte = (unsigned char)(255);
            else
               bbyte = (unsigned char)(pixels[i*(screenWidth) + j].b*255);
         }
         //Print in reverse order
         putc(bbyte, fp);
         putc(gbyte, fp);
         putc(rbyte, fp);
      }
      //cout << "\n";
      
   }

   fclose(fp);
}