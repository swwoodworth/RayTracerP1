//simple C++ code for 473 to demo class, operator overload and references
//ZJWOOD

#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <assert.h>
#include <vector>
using namespace std;

class MyVec {
  public:
    MyVec();
    MyVec(float in_x, float in_y);
    ~MyVec();
    MyVec & operator=(const MyVec &);
    friend ostream & operator<<(ostream &os, const MyVec &);
    float x, y;
  private:
   //could make data private and then write get and set functions
};

//always have a constructor which sets default values
MyVec::MyVec(void) {
  x = y = 0;
}

//a different type of constructor
MyVec::MyVec(float in_x, float in_y) {
  x = in_x;
  y = in_y;
}

//operator overloading to guarentee that "=" works the way we'd like
MyVec & MyVec::operator=(const MyVec &v1) {
  this->x = v1.x;
  this->y = v1.y;
}

//nice way to print vectors
ostream & operator<<(ostream &os, const MyVec & v1) {
  os << v1.x << " ";
  os << v1.y << endl;
}

MyVec::~MyVec() {} 

int main(void) {

  MyVec v1(1, 1);
  cout << "v1: " << v1;

  MyVec res;
  cout << "res upon construction: " << res;

  res = v1;
 
  cout << "res after setting equal to v1: " << res;
  
  return 0;
}
