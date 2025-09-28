#include <iostream>
#include <cmath>
#include "Sim.h"

Sim::Sim(int passengerCount){
    int baggage_placement_speed = 1;
    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly

    for (int i = 0; i < passengerCount; i++){
        passengerList.push_back(Person(i,6.0,3.0));
        lenPassengerList += 1;
        // position from the door to the right side of the plane
        // position from the door to the back of the plane
        // for both -1 indicates that the passenger is not on the plane yet
        // # of points moved per time increment
        // position of x seat
        // position of y seat
    }
};

void Sim::block_check(int person, blockType type_check){
    if (person == 0){;} else { // Prevent out-of-bounds
        Person* pPerson = &passengerList[person];
        switch (type_check){
            case blockType::initialBoard: // Check if anyone is in the way at the start of the plane
                if (pPerson->xPos >= passengerList[person-1].xPos and passengerList[person-1].yPos == 0){ // check if anyone is infront of them for this movement
                    pPerson->xPos = passengerList[person-1].xPos - 1; // 1 being the assumed diameter of the ideal circular humans
                }
                break;
            case blockType::centerAisle: // Check if anyone is in the way walking down the center ailse of the plane
                if (pPerson->yPos >= passengerList[person-1].yPos and passengerList[person-1].xPos == 3){ // check if anyone is infront of them for this movement
                    pPerson->yPos = passengerList[person-1].yPos - 1; // 1 being the assumed diameter of the ideal circular humans
                }
                break;
            case blockType::seatedAisle: // Check if anyone is in the way at the persons seat row
                float direction = std::signbit(3 - pPerson->xSeatPos) ? 1 : -1;         
                if (pPerson->xPos * direction >= passengerList[person-1].xPos * direction and passengerList[person].yPos == passengerList[person-1].yPos){ // check if anyone is infront of them for this movement
                    pPerson->xPos = passengerList[person-1].xPos - 1 * direction; // 1 being the assumed diameter of the ideal circular humans
                }
                break;
        }
    }
}


void Sim::move(int person, float moveSpeed){
    Person* pPerson = &passengerList[person];
    float remainMS = pPerson->moveSpeed;
    if (pPerson->yPos == 0 and pPerson->xPos != 3){ // if in starting ailse and not at center of plane...
        pPerson->xPos += moveSpeed;
        if (person > 0){
            block_check(person, blockType::initialBoard);
        } else if (pPerson->xPos >= 3){
            remainMS = 3 - pPerson->xPos -3;
            pPerson->xPos = 3;
        }
    }
    if (pPerson->xPos == 3 and pPerson->yPos != pPerson->ySeatPos and remainMS > 0){ // move down center and go to seat row
        pPerson->yPos += moveSpeed;
        if (person > 0){ // check for people in front of them
            block_check(person, blockType::centerAisle);
        } else if (pPerson->yPos >= pPerson->ySeatPos){
            remainMS = pPerson->yPos - pPerson->ySeatPos;
            pPerson->yPos = pPerson->ySeatPos;
        }
    }
    if (pPerson->yPos == pPerson->ySeatPos and remainMS > 0){
        int direction = (pPerson->xPos > pPerson->xSeatPos) ? -1 : 1;
        pPerson->xPos += direction*moveSpeed;
        if (person > 0){ // check for people in front of them
            block_check(person, blockType::seatedAisle);
        }else if (pPerson->xPos == pPerson->xSeatPos){
            pPerson->seated = true;
        }
    } // currently this sim doesn't handle interrupts. note that as of right now, if someone somehow goes past their seat the next time increment they will just hit their seat and will not care about the people around them. Potential flaw.
    
}


void Sim::step(){
    int prsnCount{0};

    while(prsnCount < nPsngr){
        if (passengerList[prsnCount].xPos != -1 and passengerList[prsnCount].seated != true) { 
            move(prsnCount, passengerList[prsnCount].moveSpeed);
        }
        prsnCount++;
    };
    if (prsnCount == lenPassengerList){;} else { // if we have everyone on the plane already, skip this step
        if (prsnCount == 0 and (passengerList[prsnCount].xPos == -1 and passengerList[prsnCount].yPos == -1)){
                passengerList[prsnCount].xPos = 0;
                passengerList[prsnCount].yPos = 0;
                nPsngr += 1;
        } else if (passengerList[prsnCount-1].xPos == -1){;} else{  // someone just boarded the plane and can't move forward, do not board another person on the plane, else ...
            if ( (passengerList[prsnCount].xPos != 0 or passengerList[prsnCount].yPos != 0) and nPsngr <= lenPassengerList ){
                passengerList[prsnCount].xPos = 0;
                passengerList[prsnCount].yPos = 0;
                nPsngr += 1;
            }
        }
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
