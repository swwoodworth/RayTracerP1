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
   
Times:  (average of 3 runs)
   recurse_simp = 3.7 sec
   recurse_simp2 = 5.6 sec
   ugly_part = 2.4 sec
   simple_refract = .42 sec
   simple_tri = .37 sec
   program3 = 1.2 sec
   

Working: 
It appears that most of the things from part 3 are fully functional, with a 
couple of exceptions.

As you can see in recurse_simp and recurse_simp2, there are some strange 
lighter areas. I believe that this may simply be an implementation 
difference that we have chosen. This occurs when a refracted or reflected ray 
does not hit anything and therefore returns nothing. You can choose to
color the object based on the things it did hit or color not add any additional
color.

The second exception can be seen in recurse_simp. My reflections are not in the
same place as you example images. I beleive I may be reflecting my rays wrong.
I will be talking to you in your office hours tomorrow about this.

My custom image is called program3.pov

Notes:
There appears to be some floating point error on my machine on the 
valentine2.pov where the two spheres overlap. This may not occur on all 
machines.

My parser only works with unix (newline) and windows (carriage return newline) 
formatted files. It will not work with the classic mac (carriage return) 
format. If the parser seg-faults please check that all .pov input file have 
the correct newlines. I have included all of the .pov that are needed for this
portion of the project in my tar file.


