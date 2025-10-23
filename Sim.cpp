#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "Sim.h"
#include "init_types.h"

enum class blockType { initialBoard, centerAisle, seatedAisle };

Sim::Sim(int passengerCount){
    int baggage_placement_speed = 1;
    // define a functions for setting the pattern of where people are sitting, call that after the foor loop to set the x and y positions correctly
    for (int i = 0; i < passengerCount; i++){
        seat_pos tempSeatPos = fullColumn(i,8);
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


int block_check(std::vector <Person> passengerList, int person, blockType type_check){
    if (person == 0){return 0;} // Prevent out-of-bounds
    Person* pPerson = &passengerList[person];
    switch (type_check){
        case blockType::initialBoard: // Check if anyone is in the way at the start of the plane
            if (pPerson->posVec[0] >= passengerList[person-1].posVec[0] and passengerList[person-1].posVec[1] == 0){ // check if anyone is infront of them for this movement
                pPerson->posVec[0] = passengerList[person-1].posVec[0] - 1; // 1 being the assumed diameter of the ideal circular humans
            }
            break;
        case blockType::centerAisle: // Check if anyone is in the way walking down the center ailse of the plane
            if (pPerson->posVec[1] >= passengerList[person-1].posVec[1] and passengerList[person-1].posVec[1] == 3){ // check if anyone is infront of them for this movement
                pPerson->posVec[1] = passengerList[person-1].posVec[1] - 1; // 1 being the assumed diameter of the ideal circular humans
            }
            break;
        case blockType::seatedAisle: // Check if anyone is in the way at the persons seat row
            float direction = std::signbit(3 - pPerson->xSeatPos) ? 1 : -1;         
            if (pPerson->posVec[0] * direction >= passengerList[person-1].posVec[0] * direction and passengerList[person].posVec[1] == passengerList[person-1].posVec[1] and not passengerList[person-1].seated){ // check if anyone is infront of them for this movement
                pPerson->posVec[0] = passengerList[person-1].posVec[0] - 1 * direction; // 1 being the assumed diameter of the ideal circular humans
            }
            break;
    }
    return 0;
};


int passed_point_check(Person* pPerson, float* remainMs, std::vector <int> direction, blockType stage){
    switch (stage){
        case blockType::initialBoard:
            if (pPerson->posVec[0] <= 3 ){*remainMs = 0.0; break;}
            *remainMs =  pPerson->posVec[0] - 3;
            pPerson->posVec[0] = 3;
            break;
        case blockType::centerAisle:
            if (pPerson->posVec[1] <= pPerson->ySeatPos ){*remainMs = 0.0; break;}
            *remainMs = pPerson->posVec[1] - pPerson->ySeatPos;
            pPerson->posVec[1] = pPerson->ySeatPos;
            break;
        case blockType::seatedAisle:
            if (pPerson->posVec[0] * direction[0] <= pPerson->xSeatPos ){*remainMs = 0.0; return 0;}
            *remainMs = pPerson->posVec[0] - pPerson->ySeatPos;
            pPerson->posVec[0] = pPerson->ySeatPos;
            break;
    }
    return 0;
};


float actually_move(Person* pPerson, float* remainMs, std::vector<int> direction , int iterator, blockType stage, std::vector <Person> passengerList){
    if (pPerson->seated){
        *remainMs = 0.0;
        return *remainMs;
    }
    pPerson->posVec[0] += direction[0] * *remainMs;
    pPerson->posVec[1] += direction[1] * *remainMs;
    if (iterator > 0){ // check for people in front of them
        block_check(passengerList, iterator, stage);
    }
    passed_point_check(pPerson, remainMs, direction, stage);
    pPerson->seated_check();
    return *remainMs;
};


int Sim::move(int person){
    Person* pPerson = &passengerList[person];
    std::vector <int> direction = {0, 0};
    float remainMs = pPerson->moveSpeed;
    float* pRemainMS = &remainMs;
    if (pPerson->posVec[1] == 0 and pPerson->posVec[0] != 3){ // if in starting ailse and not at center of plane...
        direction[0] = 1;
        direction[1] = 0;
        remainMs = actually_move(pPerson, pRemainMS, direction, person, blockType::initialBoard, passengerList);
    }
    if (pPerson->posVec[0] == 3 and pPerson->posVec[1] != pPerson->ySeatPos and remainMs > 0){ // move down center and go to seat row
        direction[0] = 0;
        direction[1] = 1;
        remainMs = actually_move(pPerson, pRemainMS, direction, person, blockType::centerAisle, passengerList);
    }
    if (pPerson->posVec[1] == pPerson->ySeatPos and remainMs > 0){
        direction[0] = (pPerson->posVec[0] > pPerson->xSeatPos) ? -1 : 1;
        direction[1] = 0;
        remainMs = actually_move(pPerson, pRemainMS, direction, person, blockType::seatedAisle, passengerList);
    } 
    return 0;


};


int Sim::step(){
    int prsnCount{0};
    while(prsnCount < nPsngr){
        if (passengerList[prsnCount].posVec[0] != -1 and passengerList[prsnCount].seated != true) { 
            move(prsnCount);
        }
        prsnCount++;
    };

    // Skip Conditions
    if ( prsnCount == 0){ }  // 1: we have everyone on the plane already
    else if (prsnCount == lenPassengerList ||passengerList[prsnCount-1].posVec[0] == -1){return 0;} // 2: someone just boarded the plane and can't move forward, do not board another person on the plane
                                                                                          
                                                                                           

    if (prsnCount == 0 and (passengerList[prsnCount].posVec[0] == -1 and passengerList[prsnCount].posVec[1] == -1)){
        passengerList[prsnCount].posVec[0] = 0; 
        passengerList[prsnCount].posVec[1] = 0;
        nPsngr += 1;
        return 0;
    } else if ( (passengerList[prsnCount-1].posVec[0] != 0 or passengerList[prsnCount-1].posVec[1] != 0) and nPsngr <= lenPassengerList ){
        passengerList[prsnCount].posVec[0] = 0;
        passengerList[prsnCount].posVec[1] = 0;
        nPsngr += 1;
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
        outputCSV << passengerList[i].posVec[0] << "," << passengerList[i].posVec[0] << ",";
    }
    outputCSV << std::endl;
}

void Sim::close_log_file(){
    outputCSV.close();
}

int Sim::run_sim(int numSteps, int numPassengers, int initPassengerType){
    for (int i{0}; i < numSteps; i++){
        if (debugMode){ display_time(i); }
        step();
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
