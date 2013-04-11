#include "RayTracer.hpp"

RayTracer::RayTracer() {
}

RayTracer::~RayTracer() {}

void RayTracer::trace(int screenWidth, int screenHeight)
{
   Pixel *pixels = (Pixel*)calloc(screenWidth * screenHeight, sizeof(Pixel));
   
   TGAWriter tga;
   tga.writeTGA(pixels, screenWidth, screenHeight);
   free(pixels);
}