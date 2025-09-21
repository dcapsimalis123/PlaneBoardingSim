#include <iostream>
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


void Sim::move(int person, float moveSpeed){ // Recursive
    Person* pPerson = &passengerList[person];
    if (pPerson->yPos == 0 and pPerson->xPos != 3){ // if in starting ailse and not at center of plane...
        pPerson->xPos += moveSpeed; // insert after this line to check for people in front of them
        if (person > 0){
            if (pPerson->xPos >= passengerList[person-1].xPos and passengerList[person-1].yPos == 0){ // check if anyone is infront of them for this movement
                pPerson->xPos = passengerList[person-1].xPos - 1; // 1 being the assumed diameter of the ideal circular humans
            }
        } else if (pPerson->xPos >= 3){
            float tempX   = pPerson->xPos - 3;
            pPerson->xPos = 3;
            move(person, tempX);
        }
    } else if (pPerson->xPos == 3 and pPerson->yPos != pPerson->ySeatPos){ // move down center and go to seat row
        pPerson->yPos += moveSpeed; // insert after this line to check for people in front of them
        if (person > 0){
            if (pPerson->yPos >= passengerList[person-1].yPos and passengerList[person-1].xPos == 3){ // check if anyone is infront of them for this movement
                pPerson->yPos = passengerList[person-1].yPos - 1; // 1 being the assumed diameter of the ideal circular humans
            }
        } else if (pPerson->yPos >= pPerson->ySeatPos){
            float tempY   = pPerson->yPos - pPerson->ySeatPos;
            pPerson->yPos = pPerson->ySeatPos;
            move(person, tempY);
        }
    } else if (pPerson->yPos == pPerson->ySeatPos){
        int direction = (pPerson->xPos > pPerson->xSeatPos) ? -1 : 1;
        pPerson->xPos += direction*moveSpeed; // insert after this line to check for people in front of them
        if (person > 0){
            if (pPerson->xPos >= passengerList[person-1].xPos and passengerList[person].yPos == passengerList[person-1].yPos){ // check if anyone is infront of them for this movement
                pPerson->xPos = passengerList[person-1].xPos - 1; // 1 being the assumed diameter of the ideal circular humans
            }
        }else if (pPerson->xPos == pPerson->xSeatPos){
            pPerson->seated = true;
        }
    } // currently this sim doesn't handle interrupts. note that as of right now, if someone somehow goes past their seat the next time increment they will just hit their seat and will not care about the people around them. Potential flaw.
    
}

// void Sim::move(int person){
//     Person* temp {&passengerList[person]};
//     if ( temp->yPos == 0){ // Move across first aisle
//         if ( (temp->xPos + temp->moveSpeed) <= 3){
//             temp->xPos += temp->moveSpeed;
//         } else {
//             temp->xPos = 3;
//             temp->yPos += temp->moveSpeed-(3-temp->xPos);
//         }
//     } else if ( temp->yPos + temp->moveSpeed >= temp->ySeatPos){ // Reached aisle but not seat. FUTURE: impliment stop here for time alloted.
//         temp->xPos -= temp->moveSpeed - (temp->ySeatPos - temp->yPos); 
//         temp->yPos = temp->ySeatPos;
//     } else {
//         temp->yPos += temp->moveSpeed;
//     } 

//     if ( temp->yPos == temp->ySeatPos and temp->xPos == temp->ySeatPos)
//     {
//         temp->seated = true; // we don't want seated passengers to move
//     }

//     temp = nullptr;
// }

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
                nPsngr       +=  1;
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

/*
constructor
destructor

*/