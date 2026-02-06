#include <iostream>
#include <vector>
#include "Person.h"

Person::Person(int tId, float temporaryXSeatPos, float temporaryYSeatPos){
    moveSpeed = 1.0;
    positionVector = {-1.0, -1.0};
    xSeatPos = temporaryXSeatPos;
    ySeatPos = temporaryYSeatPos;
    baggageSpeed = 1.0;
    baggageCompletion = 0.0;
    id = tId;
    seated = false;
}

Person::~Person(){}

void Person::baggage_placement_step(float* movementPoints){
    baggageCompletion += baggageSpeed * *movementPoints;
    if (baggageCompletion >= 1.0){
        *movementPoints = (baggageCompletion - 1.0)/baggageSpeed;
        *movementPoints = (*movementPoints > 0.0) ? *movementPoints : 0.0;
    } else {
        *movementPoints = 0.0;
    }
}