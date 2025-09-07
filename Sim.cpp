#include <iostream>
#include "Sim.h"

Sim::Sim(int passengerCount){
    int baggage_placement_speed = 1;
    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly

    for (int i = 0; i < passengerCount; i++){
        xPos.push_back(-1); // position from the door to the right side of the plane
        yPos.push_back(-1); // position from the door to the back of the plane
                            // for both -1 indicates that the passenger is not on the plane yet
        moveSpeed.push_back(1); // # of points moved per time increment
        xSeatPos.push_back(0); // position of x seat
        ySeatPos.push_back(3); // position of y seat
        id.push_back(i);
        seated.push_back(false);
    }
};

void Sim::move(int person){
    int* xPosTemp {&xPos[person]};
    int* yPosTemp {&yPos[person]};
    int* xSeatPosTemp {&xSeatPos[person]};
    int* ySeatPosTemp {&ySeatPos[person]};
    int* moveSpeedTemp {&moveSpeed[person]};


    if ( *yPosTemp == 0){
        if ( (*xPosTemp + *moveSpeedTemp) <= 3){
            *xPosTemp += *moveSpeedTemp;
        }else{
            *xPosTemp = 3;
            *yPosTemp += *moveSpeedTemp-(3-*xPosTemp);
        }
    } else if ( *yPosTemp + *moveSpeedTemp >= *ySeatPosTemp){ // Reached aisle but not seat. FUTURE: impliment stop here for time alloted.
        *xPosTemp  -= *moveSpeedTemp - (*ySeatPosTemp - *yPosTemp); 
        *yPosTemp  = *ySeatPosTemp;
    } else {
        *yPosTemp += *moveSpeedTemp;
    }    
    if ( *yPosTemp == *ySeatPosTemp and *xPosTemp == *xSeatPosTemp)
    {
        seated[person] = true; // we don't want seated passengers to move
    }
}

void Sim::step(){

    for(int person = 0; person < nPsngr; person++){
        // Movement definition
        if (seated[person] != 1) { 
            move(person);
        }
    }
    if (nPsngr == 0 and (xPos[0] == -1 and yPos[0] == -1)){
        xPos[0] = 0;
        yPos[0] = 0;
        nPsngr += 1;
    } else if ( (xPos[nPsngr-1] != 0 or yPos[nPsngr-1] != 0) and nPsngr <= passengerCount ){
        xPos[nPsngr]  =  0;
        yPos[nPsngr]  =  0;
        nPsngr       +=  1;
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
};

/*
constructor
destructor

*/