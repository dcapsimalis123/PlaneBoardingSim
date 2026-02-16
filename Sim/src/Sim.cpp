#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Sim.h"
#include "Globals.h"
#include <atomic>

enum class blockType { initialBoard, centerAisle, seatedAisle };

Sim::Sim(Global::Globals* globalValues, seat_pos (*seatingType)(int, Global::Globals*)){
    // initialization overload from before there were global inputs
    int baggage_placement_speed = 1;

    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly
    for (int i = 0; i < globalValues->passengerCount; i++){
        seat_pos tempSeatPos = seatingType(i, globalValues);
        passengerList.push_back(Person(i,tempSeatPos.xSeatPos,tempSeatPos.ySeatPos));
        lenPassengerList += 1;
        // position from the door to the right side of the plane
        // position from the door to the back of the plane
        // for both -1 indicates that the passenger is not on the plane yet
        // # of points moved per time increment
        // position of x seat
        // position of y seat
    }
    start_log_file();
};

Sim::Sim(Global::Globals* globalValues,  seat_pos (*seatingType)(int, Global::Globals*), int iplaneLength, int iplaneWidth){
    // initialization overload from before there were global inputs
    int baggage_placement_speed = 1;
    globalValues->planeLength   = iplaneLength;
    globalValues->planeMidPoint = iplaneWidth;
    globalValues->planeWidth    = iplaneWidth/2;


    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly
    for (int i = 0; i < globalValues->passengerCount; i++){
        seat_pos tempSeatPos = seatingType(i, globalValues);
        passengerList.push_back(Person(i,tempSeatPos.xSeatPos,tempSeatPos.ySeatPos));
        lenPassengerList += 1;
        // position from the door to the right side of the plane
        // position from the door to the back of the plane
        // for both -1 indicates that the passenger is not on the plane yet
        // # of points moved per time increment
        // position of x seat
        // position of y seat
    }
    start_log_file();
};


int block_check(std::vector<Person>& passengerList, int person, blockType type_check, Global::Globals* globalValues){
    // this determines where in the plane the passenger is and thus what differences between the individual and those ahead of them might constitute a blockage that would inhibit movement
    if (person == 0){return -1;} // Prevent out-of-bounds
    Person* pPerson = &passengerList[person];
    switch (type_check){
        case blockType::initialBoard: // Check if anyone is in the way at the start of the plane
            if (pPerson->positionVector[0] >= passengerList[person-1].positionVector[0] && passengerList[person-1].positionVector[1] == 0){ // check if anyone is infront of them for this movement
                pPerson->positionVector[0] = passengerList[person-1].positionVector[0] - 1; // 1 being the assumed diameter of the ideal circular humans
            }
            break;
        case blockType::centerAisle: // Check if anyone is in the way walking down the center ailse of the plane
            if (pPerson->positionVector[1] >= passengerList[person-1].positionVector[1] && passengerList[person-1].positionVector[0] == globalValues->planeMidPoint){ // check if anyone is infront of them for this movement
                pPerson->positionVector[1] = passengerList[person-1].positionVector[1] - 1; // 1 being the assumed diameter of the ideal circular humans
            }
            break;
        case blockType::seatedAisle: // Check if anyone is in the way at the persons seat row
            float direction = std::signbit(globalValues->planeMidPoint - pPerson->xSeatPos) ? 1 : -1;         
            if (pPerson->positionVector[0] * direction >= passengerList[person-1].positionVector[0] * direction && passengerList[person].positionVector[1] == passengerList[person-1].positionVector[1] && !passengerList[person-1].seated){ // check if anyone is infront of them for this movement
                pPerson->positionVector[0] = passengerList[person-1].positionVector[0] - 1 * direction; // 1 being the assumed diameter of the ideal circular humans
            }
            break;
    }
    return 0;
};


int passed_point_check(Person* pPerson, float* movementPoints, std::vector<int>& direction, blockType stage, Global::Globals* globalValues){
    // This function takes in a person pointer and the type of blocking determined elsewhere, and "bounce" the person back if they have overstepped
    switch (stage){
        case blockType::initialBoard:
            if (pPerson->positionVector[0] <= globalValues->planeMidPoint ){*movementPoints = 0.0; break;}
            *movementPoints =  pPerson->positionVector[0] - globalValues->planeMidPoint;
            pPerson->positionVector[0] = globalValues->planeMidPoint;
            break;
        case blockType::centerAisle:
            if (pPerson->positionVector[1] <= pPerson->ySeatPos ){*movementPoints = 0.0; break;}
            *movementPoints = pPerson->positionVector[1] - pPerson->ySeatPos;
            pPerson->positionVector[1] = pPerson->ySeatPos;
            break;
        case blockType::seatedAisle:
            if (pPerson->positionVector[0] * direction[0] <= pPerson->xSeatPos ){*movementPoints = 0.0; return 0;}
            *movementPoints = pPerson->positionVector[0] - pPerson->xSeatPos;
            pPerson->positionVector[0] = pPerson->ySeatPos;
            break;
    }
    return 0;
};


float position_change(Person* pPerson, float* movementPoints, std::vector<int>& direction , int iterator, blockType stage, std::vector<Person>& passengerList, Global::Globals* globalValues){
    // this moves the person regardless of whats in front of them, then selects how it should determine if its moved too far, move them back if needed, then checks if the person is at their seat
    // returns movement points incase there is extra movement left in a time cycle, which means they could also move through the rest of the timer.
    if (pPerson->seated){
        *movementPoints = 0.0;
        return *movementPoints;
    }
    pPerson->positionVector[0] += direction[0] * *movementPoints;
    pPerson->positionVector[1] += direction[1] * *movementPoints;
    if (iterator > 0){ // check for people in front of them
        block_check(passengerList, iterator, stage, globalValues);
    }
    passed_point_check(pPerson, movementPoints, direction, stage, globalValues);
    pPerson->seated_check();
    return *movementPoints;
};


int Sim::move(int person, Global::Globals* globalValues){
    // highest part of the controling of the movement for the person objects. instantiates their movement for the time cycle, figures out how they should move given starting position,
    // and then finally it does the actual movemnet for a given section. If there is spare movement, then it continues moving down the next section (ie if 2 movement points at a turn, it will move to the turn and then turn)
    Person* pPerson = &passengerList[person];
    std::vector<int> direction = {0, 0};
    float movementPoints = pPerson->moveSpeed;
    float* pmovementPoints = &movementPoints;
    if (pPerson->positionVector[1] == 0 && pPerson->positionVector[0] < globalValues->planeMidPoint){ // if in starting ailse and not at center of plane...
        direction[0] = 1;
        direction[1] = 0;
        movementPoints = position_change(pPerson, pmovementPoints, direction, person, blockType::initialBoard, passengerList, globalValues);
    }
    if (pPerson->positionVector[0] == globalValues->planeMidPoint && pPerson->positionVector[1] < pPerson->ySeatPos && movementPoints > 0){ // move down center && go to seat row
        direction[0] = 0;
        direction[1] = 1;
        movementPoints = position_change(pPerson, pmovementPoints, direction, person, blockType::centerAisle, passengerList, globalValues);
    }
    if (pPerson->positionVector[1] == pPerson->ySeatPos && movementPoints > 0){
        direction[0] = (pPerson->positionVector[0] > pPerson->xSeatPos) ? -1 : 1;
        direction[1] = 0;
        if (pPerson->baggageCompletion < 1.0){
            float* tempmovementPoints = &movementPoints;
            pPerson->baggage_placement_step(tempmovementPoints);
        }
        movementPoints = position_change(pPerson, pmovementPoints, direction, person, blockType::seatedAisle, passengerList, globalValues);
    } 
    return 0;


};


int Sim::step(Global::Globals* globalValues){
    // This is the largest controller of a time cycle step for the Sim
    int personIterator{0};
    while(personIterator < passengersBoarding){
        if (passengerList[personIterator].positionVector[0] != -1 && passengerList[personIterator].seated != true) { 
            move(personIterator, globalValues);
        }
        personIterator++;
    };

    // Skip Conditions
    if ( personIterator == 0){ }  // 1: we have everyone on the plane already
    else if (personIterator == lenPassengerList ||passengerList[personIterator-1].positionVector[0] == -1){return 0;} // 2: someone just boarded the plane && can't move forward, do not board another person on the plane

    if (personIterator == 0 && (passengerList[personIterator].positionVector[0] == -1 && passengerList[personIterator].positionVector[1] == -1)){
        passengerList[personIterator].positionVector[0] = 0; 
        passengerList[personIterator].positionVector[1] = 0;
        passengersBoarding += 1;
        return 0;
    } else if ( (passengerList[personIterator-1].positionVector[0] != 0 || passengerList[personIterator-1].positionVector[1] != 0) && passengersBoarding <= lenPassengerList ){
        passengerList[personIterator].positionVector[0] = 0;
        passengerList[personIterator].positionVector[1] = 0;
        passengersBoarding += 1;
        return 0;
    }
    return 0;
};

void Sim::display_seatPoses(){
    for (int i = 0; i < lenPassengerList; i++){
        passengerList[i].display_seatPos();
    }
};


void Sim::start_log_file(){
    outputCSV.open("Outputs/output.csv");
    outputCSV << "First Line";
    for (int i=0; i<lenPassengerList*2; i++){
        outputCSV << ",";
    }
    outputCSV << std::endl;
    
    for (int i =0 ; i < lenPassengerList; i++ ){
        outputCSV << i << ", , ";
    }
    outputCSV << std::endl;
    for (int i =0 ; i < lenPassengerList; i++ ){
        outputCSV << "x, y, ";
    }
    outputCSV << std::endl;
}

void Sim::update_log_file(){
    for (int i =0 ; i < lenPassengerList; i++ ){
        outputCSV << passengerList[i].positionVector[0] << "," << passengerList[i].positionVector[1] << ",";
    }
    outputCSV << std::endl;
}

void Sim::close_log_file(){
    outputCSV.close();
}

int Sim::run_sim(int numSteps, int numPassengers, int initPassengerType, Global::Globals* globalValues){
    for (int i{0}; i < numSteps; i++){
        if (debugMode){ display_time(i); }
        step(globalValues);
        update_log_file();
    }
    return 0;
};

void Sim::display_time(int iteratorStep){
    std::cout << "Time: " << iteratorStep << std::endl;
    for (int j = 0; j < lenPassengerList; j++){
        std::cout << "Person " << j+1 << " is at ";
        display_pos(j);
    }
};
