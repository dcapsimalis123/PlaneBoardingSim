#include <iostream>
#include <vector>
#include "Person.h"

Person::Person(int tId, float txSeatPos, float tySeatPos){
    xPos = -1.0;
    yPos = -1.0;
    moveSpeed = 1.0;
    xSeatPos = txSeatPos;
    ySeatPos = tySeatPos;
    id = tId;
    seated = false;
}

Person::~Person(){}