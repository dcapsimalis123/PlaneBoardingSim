#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Sim.h"
#include "Globals.h"

enum class blockType { initialBoard, centerAisle, seatedAisle };

Sim::Sim(int passengerCount, Global::Globals* globalValues, seat_pos (*seatingType)(int, Global::Globals*)){
    int baggage_placement_speed = 1;

    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly
    for (int i = 0; i < passengerCount; i++){
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

Sim::Sim(int passengerCount, Global::Globals* globalValues,  seat_pos (*seatingType)(int, Global::Globals*), int iplaneLength, int iplaneWidth){
    int baggage_placement_speed = 1;
    globalValues->planeLength   = iplaneLength;
    globalValues->planeMidPoint = iplaneWidth;
    globalValues->planeWidth    = iplaneWidth/2;


    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly
    for (int i = 0; i < passengerCount; i++){
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
    if (person == 0){return 0;} // Prevent out-of-bounds
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


int passed_point_check(Person* pPerson, float* remainMs, std::vector<int>& direction, blockType stage, Global::Globals* globalValues){
    switch (stage){
        case blockType::initialBoard:
            if (pPerson->positionVector[0] <= globalValues->planeMidPoint ){*remainMs = 0.0; break;}
            *remainMs =  pPerson->positionVector[0] - globalValues->planeMidPoint;
            pPerson->positionVector[0] = globalValues->planeMidPoint;
            break;
        case blockType::centerAisle:
            if (pPerson->positionVector[1] <= pPerson->ySeatPos ){*remainMs = 0.0; break;}
            *remainMs = pPerson->positionVector[1] - pPerson->ySeatPos;
            pPerson->positionVector[1] = pPerson->ySeatPos;
            break;
        case blockType::seatedAisle:
            if (pPerson->positionVector[0] * direction[0] <= pPerson->xSeatPos ){*remainMs = 0.0; return 0;}
            *remainMs = pPerson->positionVector[0] - pPerson->xSeatPos;
            pPerson->positionVector[0] = pPerson->ySeatPos;
            break;
    }
    return 0;
};


float position_change(Person* pPerson, float* remainMs, std::vector<int>& direction , int iterator, blockType stage, std::vector<Person>& passengerList, Global::Globals* globalValues){
    if (pPerson->seated){
        *remainMs = 0.0;
        return *remainMs;
    }
    pPerson->positionVector[0] += direction[0] * *remainMs;
    pPerson->positionVector[1] += direction[1] * *remainMs;
    if (iterator > 0){ // check for people in front of them
        block_check(passengerList, iterator, stage, globalValues);
    }
    passed_point_check(pPerson, remainMs, direction, stage, globalValues);
    pPerson->seated_check();
    return *remainMs;
};


int Sim::move(int person, Global::Globals* globalValues){
    Person* pPerson = &passengerList[person];
    std::vector<int> direction = {0, 0};
    float remainMs = pPerson->moveSpeed;
    float* pRemainMS = &remainMs;
    if (pPerson->positionVector[1] == 0 && pPerson->positionVector[0] != globalValues->planeMidPoint){ // if in starting ailse and not at center of plane...
        direction[0] = 1;
        direction[1] = 0;
        remainMs = position_change(pPerson, pRemainMS, direction, person, blockType::initialBoard, passengerList, globalValues);
    }
    if (pPerson->positionVector[0] == globalValues->planeMidPoint && pPerson->positionVector[1] != pPerson->ySeatPos && remainMs > 0){ // move down center && go to seat row
        direction[0] = 0;
        direction[1] = 1;
        remainMs = position_change(pPerson, pRemainMS, direction, person, blockType::centerAisle, passengerList, globalValues);
    }
    if (pPerson->positionVector[1] == pPerson->ySeatPos && remainMs > 0){
        direction[0] = (pPerson->positionVector[0] > pPerson->xSeatPos) ? -1 : 1;
        direction[1] = 0;
        if (pPerson->baggageCompletion < 1.0){
            float* tempRemainMs = &remainMs;
            pPerson->baggage_placement_step(tempRemainMs);
        }
        remainMs = position_change(pPerson, pRemainMS, direction, person, blockType::seatedAisle, passengerList, globalValues);
    } 
    return 0;


};


int Sim::step(Global::Globals* globalValues){
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
    outputCSV.open("output.csv");
    outputCSV << "First Line" << std::endl;
    
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
