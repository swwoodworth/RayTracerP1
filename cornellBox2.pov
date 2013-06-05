// Cornell Box
// Adapted from original
// Spencer Woodworth

camera {
  location  <0, 5, 15.5>
  up        <0,  1,  0>
  right     <1, 0,  0>
  look_at   <0, 5, 0>
}

light_source {<0, 5, 15> color rgb <0.1, 0.1, 0.1>}
light_source {<0, 9.5, 0> color rgb <0.5, 0.5, 0.5>}

//Short box
box { <-1,-1,-1>, <1,1,1>
   rotate <0, -20, 0>
   scale 1.5
   translate <1.5, 1.5, 1.5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}

//Tall box
box { <-1,-1,-1>, <1,1,1>
   rotate <0, 20, 0>
   scale <1.5, 3, 1.5>
   translate <-2, 3, -2>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <-2, 2, 0>
}

sphere { <0, 0, 0>, 1.5
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <1.5, 4.5, 1>
}

sphere { <0, 0, 0>, 1.5
  pigment { color rgb <0.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <0, 7, -4>
}

// THE ROOM

// floor @ y=0
triangle { <-5,0,5>, <5,0,-5>, <-5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <-5,0,5>, <5,0,5>, <5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}

// right wall
triangle { <5,0,5>, <5,10,5>, <5,0,-5>
   pigment { color rgb <0,0.7,0> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <5,10,5>, <5,10,-5>, <5,0,-5>
   pigment { color rgb <0,0.7,0> }
   finish { ambient 0.20 diffuse 0.8 }
}

// left wall
triangle { <-5,0,5>, <-5,0,-5>, <-5,10,-5>
   pigment { color rgb <0.7,0,0> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <-5,10,5>, <-5,0,5>, <-5,10,-5>
   pigment { color rgb <0.7,0,0> }
   finish { ambient 0.20 diffuse 0.8 }
}

// back wall
triangle { <5,10,-5>, <-5,10,-5>, <5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <5,0,-5>, <-5,10,-5>, <-5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}

// ceiling @ y=10, w/ a 1x1 hole in the middle
//big left part
triangle { <-5,10,5>, <-5,10,-5>, <-1,10,5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <-1,10,5>, <-5,10,-5>, <-1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
//big right part
triangle { <5,10,5>, <1,10,5>, <1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <5,10,5>, <1,10,-5>, <5,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
//little front part
triangle { <-1,10,5>, <1,10,1>, <1,10,5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <-1,10,5>, <-1,10,1>, <1,10,1>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
//little back part
triangle { <-1,10,-1>, <1,10,-5>, <1,10,-1>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}
triangle { <-1,10,-1>, <-1,10,-5>, <1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0.20 diffuse 0.8 }
}



