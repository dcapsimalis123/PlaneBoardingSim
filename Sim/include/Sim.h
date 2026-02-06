#include <iostream>
#include <vector>
#include <fstream>
#include "BoardingTypes.h"
#include "Person.h"
#include "Globals.h"



class Sim {
private:
    int passengerCount{1};
    int passengersBoarding{0}; // This is technically the amount on the plane, but this wording is more pithy
    bool simEnd = false;
    bool debugMode = true;
    std::vector<Person> passengerList;
    int  move(int person, Global::Globals* globalValues);
    int  step(Global::Globals* globalValues);
    std::ofstream outputCSV;
public:
    // Constructor
    Sim(Global::Globals* globalValues, seat_pos (*seatingType)(int, Global::Globals*));
    Sim(Global::Globals* globalValues, seat_pos (*seatingType)(int, Global::Globals*), int planeLength, int planeWidth);

    // Destructor

    // needed values
    int  lenPassengerList{0};

    // regular functions
    int  run_sim(int numSteps, int numPassengers, int initPassengerType, Global::Globals* globalValues);
    int  display_id(int psngCount){return passengerList[psngCount].id;};
    void display_pos(int psngCount){passengerList[psngCount].display_pos();};
    void display_seatPoses();

    void start_log_file();
    void update_log_file();
    void close_log_file();
    void display_time(int iteratorStep);
};
