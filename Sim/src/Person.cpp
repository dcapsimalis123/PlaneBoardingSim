#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "Person.h"

Person::Person(int tId, float txSeatPos, float tySeatPos){
    moveSpeed = 1.0;
    positionVector = {-1.0, -1.0};
    xSeatPos = txSeatPos;
    ySeatPos = tySeatPos;
    baggageSpeed = 1.0;
    baggageCompletion = 0.0;
    id = tId;
    seated = false;
}

Person::~Person(){}

void Person::baggage_placement_step(float* remainMs){
    baggageCompletion += baggageSpeed * *remainMs;
    if (baggageCompletion <= 1.0){
        *remainMs = (baggageCompletion - 1.0)/baggageSpeed;
        *remainMs = (*remainMs > 0.0) ? *remainMs : 0.0;
    } else {
        *remainMs = 0.0;
    }
}