// cs473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <5, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

sphere { <0, 0, 0>, 2
  pigment { color rgb <1.0, 0.0, 0.0>}
  finish {ambient 0.2 diffuse 0.8}
  translate <12, -2, -4>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.98, 0.47, 0.0>}
  finish {ambient 0.2 diffuse 0.8}
  translate <11, -2, 2>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.98, 0.98, 0.0>}
  finish {ambient 0.2 diffuse 0.8}
  translate <9, -2, 7>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.0, 0.98, 0.3>}
  finish {ambient 0.2 diffuse 0.8}
  translate <6, -2, 11>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.0, 0.03, 0.83>}
  finish {ambient 0.2 diffuse 0.8}
  translate <2, -2, 14>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.71, 0.00, 0.65>}
  finish {ambient 0.2 diffuse 0.8}
  translate <-3, -2, 16>
}

//

sphere { <0, 0, 0>, 2
  pigment {color rgbf <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.2 diffuse 0.2 refraction 1.0 ior 1.9}
  translate <0, 2, 3>
}

sphere { <0, 0, 0>, 2
  pigment { color rgb <0.51, 0.51, 0.55>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.8}
  translate <0, -2, -1>
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
}


