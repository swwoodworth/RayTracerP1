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
   0 - none
   4 - 4X
   9 - 9X

To Run: 
   $ make
   $ ./RayTracer 640 480 -I simple.pov 0 9
   
Times:  (average of 3 runs)
   balls2 - 7.5 seconds 
   gnarly - 23 seconds
   bunny_large - 1.8 seconds
   program4 - 5.5 seconds
   

Working: 
All of the features of program 4 appear to be working with some exceptions. 
Both gnarly.pov and balls2.pov do not look correct (see handin images). 
However, I ran these files with my part3 code (it took about 4 mins to run)
and got the same image. This means that whatever bug is leading to the 
missing/smaller spheres was pre-existing. I don't know what to do at this point
to debug. 

My custom image is called program4.pov

Notes:
There appears to be some floating point error on my machine on the 
valentine2.pov where the two spheres overlap. This may not occur on all 
machines.

My parser only works with unix (newline) and windows (carriage return newline) 
formatted files. It will not work with the classic mac (carriage return) 
format. If the parser seg-faults please check that all .pov input file have 
the correct newlines. I have included all of the .pov that are needed for this
portion of the project in my tar file.


