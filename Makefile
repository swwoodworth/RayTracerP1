OBJS = Main.o RayTracerObject.o ShadingModel.o CameraObj.o LightSourceObj.o TranslateObj.o \
       ScaleObj.o RotateObj.o PigmentObj.o FinishObj.o SphereObj.o BoxObj.o \
       ConeObj.o PlaneObj.o TriangleObj.o Geometry.o RayTracer.o TGAWriter.o
CC = g++
DEBUG = -g
CFLAGS = -O2 -Wall -Werror -c $(DEBUG)
LFLAGS = -O2 -Wall -Werror $(DEBUG)

RayTracer : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o RayTracer
	
Main.o : Main.cpp
	$(CC) $(CFLAGS) Main.cpp
	
ShadingModel.o : ShadingModel.hpp ShadingModel.cpp
	$(CC) $(CFLAGS) ShadingModel.cpp

RayTracerObject.o : RayTracerObject.hpp RayTracerObject.cpp
	$(CC) $(CFLAGS) RayTracerObject.cpp
	
CameraObj.o : CameraObj.hpp CameraObj.cpp
	$(CC) $(CFLAGS) CameraObj.cpp
	
LightSourceObj.o : LightSourceObj.hpp LightSourceObj.cpp
	$(CC) $(CFLAGS) LightSourceObj.cpp

TranslateObj.o : TranslateObj.hpp TranslateObj.cpp
	$(CC) $(CFLAGS) TranslateObj.cpp

ScaleObj.o : ScaleObj.hpp ScaleObj.cpp
	$(CC) $(CFLAGS) ScaleObj.cpp

RotateObj.o : RotateObj.hpp RotateObj.cpp
	$(CC) $(CFLAGS) RotateObj.cpp
	
PigmentObj.o : PigmentObj.hpp PigmentObj.cpp
	$(CC) $(CFLAGS) PigmentObj.cpp

FinishObj.o : FinishObj.hpp FinishObj.cpp
	$(CC) $(CFLAGS) FinishObj.cpp

SphereObj.o : SphereObj.hpp SphereObj.cpp
	$(CC) $(CFLAGS) SphereObj.cpp
	
BoxObj.o : BoxObj.hpp BoxObj.cpp
	$(CC) $(CFLAGS) BoxObj.cpp
	
ConeObj.o : ConeObj.hpp ConeObj.cpp
	$(CC) $(CFLAGS) ConeObj.cpp

PlaneObj.o : PlaneObj.hpp PlaneObj.cpp
	$(CC) $(CFLAGS) PlaneObj.cpp
	
TriangleObj.o : TriangleObj.hpp TriangleObj.cpp
	$(CC) $(CFLAGS) TriangleObj.cpp

Geometry.o : Geometry.hpp Geometry.cpp
	$(CC) $(CFLAGS) Geometry.cpp
	
RayTracer.o : RayTracer.hpp RayTracer.cpp
	$(CC) $(CFLAGS) RayTracer.cpp
	
TGAWriter.o : TGAWriter.hpp TGAWriter.cpp
	$(CC) $(CFLAGS) TGAWriter.cpp

clean:
	\rm *.o RayTracer

tar:
	tar cfv rayTracer.tar RayTracerObject.hpp RayTracerObject.cpp \
	         ShadingModel.hpp ShadingModel.cpp \
	         CameraObj.hpp CameraObj.cpp \
	         LightSourceObj.hpp LightSourceObj.cpp \
	         TranslateObj.hpp TranslateObj.cpp \
	         ScaleObj.hpp ScaleObj.cpp \
	         RotateObj.hpp RotateObj.cpp \
	         PigmentObj.hpp PigmentObj.cpp \
	         FinishObj.hpp FinishObj.cpp \
	         SphereObj.hpp SphereObj.cpp \
	         BoxObj.hpp BoxObj.cpp \
	         ConeObj.hpp ConeObj.cpp \
	         PlaneObj.hpp PlaneObj.cpp \
	         TriangleObj.hpp TriangleObj.cpp \
	         Geometry.hpp Geometry.cpp \
	         RayTracer.hpp RayTracer.cpp \
	         TGAWriter.hpp TGAWriter.cpp \
	         glm README.txt \
	         *.pov *.tga \
            Main.cpp Makefile
            
tarImage:
	tar cfv images.tar *.tga
	
tarPOV:
	tar cfv povray.tar *.pov
