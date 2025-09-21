#include <iostream>
#include <vector>
#include "Person.h"

class Sim {
private:
    int passengerCount{1};
    int nPsngr{0};
    bool simEnd = false;
    std::vector<Person> passengerList;
    // void move(int person);
    void move(int person, float moveSpeed);
    bool block_check(int person, std::string type_check);
public:
    int lenPassengerList{0};
    Sim(int passengerCount);
    int  display_id(int psngCount){return passengerList[psngCount].id;};
    void display_pos(int psngCount){passengerList[psngCount].display_pos();};
    void step();
    
    //getters


    //setters


    
};
