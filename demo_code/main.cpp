/*
  Very simple c++ file showing object inheritence and the use of virtual functions for CPE 473
  Z. Wood April 2013
*/
#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <assert.h>
#include <vector>

using namespace std;

/* base class */
class MyGeomObj {
  public:
    MyGeomObj(); //constructor
    MyGeomObj(int id); //alternate constructor
    ~MyGeomObj(); //destructor (apparently bad form :)
    virtual void printID() {cout << "dummy" << endl;}; //base class print function
    int ObjID; //base class public data
};

/* always set variables in your default constructor */ 
MyGeomObj::MyGeomObj() {
  ObjID = -1;
}

/* alternative constructor */
MyGeomObj::MyGeomObj(int in_ID) {
  ObjID = in_ID;
}

MyGeomObj::~MyGeomObj() {}

/* derived class  - circle*/
class CircObj : public MyGeomObj {
  public:
    CircObj();
    CircObj(int id);
    ~CircObj();
    void printID() { cout << "circle " << ObjID << endl;}; //a different implementation of the print fn
};

CircObj::CircObj() {
  ObjID = -2;
}

CircObj::CircObj(int in_ID) {
  ObjID = in_ID;
}

CircObj::~CircObj() {}

/* derived class  - square*/
class SqObj : public MyGeomObj {
  public:
    SqObj();
    SqObj(int id);
    ~SqObj();
    void printID() { cout << "square " << ObjID << endl;};
};

SqObj::SqObj() {
  ObjID = -2;
}

SqObj::SqObj(int in_ID) {
  ObjID = in_ID;
}

SqObj::~SqObj() {}

/*An STL vector to hold all my objects */
vector<MyGeomObj*> TheObjects;


int main(void) {

  /* make 3 different types of objects */
  MyGeomObj *C1 = new CircObj(1);
  MyGeomObj *S1 = new SqObj(2);
  MyGeomObj *GO = new MyGeomObj(123);

  /* put them on the list of objects */
  TheObjects.push_back(GO);
  TheObjects.push_back(C1);
  TheObjects.push_back(S1);

  cout << "Printing individually" << endl;
  C1->printID();
  S1->printID();
  GO->printID();

  cout << "Printing from a list - note order:" << endl;
  
  for (int i=0; i < 3; i++) {
   TheObjects[i]->printID();
  }

  /* clean up the memory I newed */
  delete C1;
  delete S1;
  delete GO;

  return 0;
}

