#include <iostream>
#include <vector>
#include "Person.h"

Person::Person(int tId, float txSeatPos, float tySeatPos){
    moveSpeed = 1.0;
    posVec = {-1.0, -1.0};
    xSeatPos = txSeatPos;
    ySeatPos = tySeatPos;
    id = tId;
    seated = false;
}

Person::~Person(){}