README

Spencer Woodworth
CSC 473 Ray Tracer

This make file will run and code will compile on a mac.

Usage: 
   RayTracer imageWidth imageHeight -I inputFilename.pov shadingMode antialiasLevel

Shading Modes:
   0 - Phong
   1 - Gaussian
   
Anti-alias Levels:
   1 - none
   4 - 4X
   9 - 9X

To Run: 
   $ make
   $ ./RayTracer 480 480 -I cornellBox2.pov 0 0
   
Test File:
   cornellBox - 1:37
   cornellBox2 - 2:06

Working: 
Global illumination is fully working! I created cornellBox2.pov as a custom
image to test the global illumination. The test images were created using 1
level of recursion and 256 rays, however my software is capable of using 
an indefinite number of resurses.

Notes:

My parser only works with unix (newline) and windows (carriage return newline) 
formatted files. It will not work with the classic mac (carriage return) 
format. If the parser seg-faults please check that all .pov input file have 
the correct newlines. I have included all of the .pov that are needed for this
portion of the project in my tar file.


