README

Spencer Woodworth
CSC 473 Ray Tracer

This make file will run and code will compile on a mac.

Usage: 
   RayTracer imageWidth imageHeight -I inputFilename.pov shadingMode

Shading Modes:
   0 - Phong
   1 - Gaussian

To Run: 
   $ make
   $ ./RayTracer 640 480 -I simple.pov 0
   

Working: 
All features required for Program Part 2 are working. 

Notes:
There appears to be some floating point error on my machine on the 
valentine2.pov where the two spheres overlap. This may not occur on all 
machines.

My parser only works with unix (newline) and windows (carriage return newline) 
formatted files. It will not work with the classic mac (carriage return) 
format. If the parser seg-faults please check that all .pov input file have 
the correct newlines. I have included all of the .pov that are needed for this
portion of the project in my tar file.


