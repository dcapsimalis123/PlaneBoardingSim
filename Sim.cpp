#include <iostream>
#include "Sim.h"

Sim::Sim(int passengerCount){
    int baggage_placement_speed = 1;
    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly

    for (int i = 0; i < passengerCount; i++){
        passengerList[i] = Person(i,0,3);
        // position from the door to the right side of the plane
        // position from the door to the back of the plane
        // for both -1 indicates that the passenger is not on the plane yet
        // # of points moved per time increment
        // position of x seat
        // position of y seat
    }
};

void Sim::move(int person){
    Person* temp {&passengerList[person]};
    if ( temp->yPos == 0){
        if ( (temp->xPos + temp->moveSpeed) <= 3){
            temp->xPos += temp->moveSpeed;
        } else {
            temp->xPos = 3;
            temp->yPos += temp->moveSpeed-(3-temp->xPos);
        }
    } else if ( temp->yPos + temp->moveSpeed >= temp->ySeatPos){ // Reached aisle but not seat. FUTURE: impliment stop here for time alloted.
        temp->xPos -= temp->moveSpeed - (temp->ySeatPos - temp->yPos); 
        temp->yPos = temp->ySeatPos;
    } else {
        temp->yPos += temp->moveSpeed;
    } 

    if ( temp->yPos == temp->ySeatPos and temp->xPos == temp->ySeatPos)
    {
        temp->seated = true; // we don't want seated passengers to move
    }

    delete temp;
}

void Sim::step(){
    int prsnCount{0};

    while(prsnCount < nPsngr){
        if (passengerList[prsnCount].seated == true) { 
            move(prsnCount);
        }
        prsnCount++;
    };

    if (prsnCount == 0 and (passengerList[prsnCount].xPos == -1 and passengerList[prsnCount].yPos == -1)){
        passengerList[prsnCount].xPos = 0;
        passengerList[prsnCount].yPos = 0;
        prsnCount += 1;
    } else if ( (passengerList[prsnCount].xPos != 0 or passengerList[prsnCount].yPos != 0) and nPsngr <= passengerCount ){
        passengerList[prsnCount].xPos = 0;
        passengerList[prsnCount].yPos = 0;
        prsnCount       +=  1;
    }
    /*
    move first moving passenger currently on plane 
        *check if loading baggage
        move will be check to see if anyone is inline they are trying to move then if not move them full 1, if there is stop at spot before
        if move brings you to Y pos of your seat, stop at Y position and move the rest in X direction.
    loop move down to before nPsngr Waiting
    once we reach that step, if next passeneger value != length of position values check if 0,0 is open
    if open, move newest passenger (position and values at -1,-1 and position nPsngrWaiting) to 0,0 and iterate nPsngr, if not skip
    end step
    */
}

/*
constructor
destructor

*/