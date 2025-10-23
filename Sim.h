#include <iostream>
#include <vector>
#include <fstream>
#include "Person.h"



class Sim {
private:
    int passengerCount{1};
    int nPsngr{0};
    bool simEnd = false;
    bool debugMode = true;
    std::vector<Person> passengerList;
    int  move(int person);
    int  step();
    std::ofstream outputCSV;
public:
    // Constructor
    Sim(int passengerCount);

    // Destructor

    // needed values
    int  lenPassengerList{0};

    // regular functions
    int  run_sim(int numSteps, int numPassengers, int initPassengerType);
    int  display_id(int psngCount){return passengerList[psngCount].id;};
    void display_pos(int psngCount){passengerList[psngCount].display_pos();};
    void display_seatPoses();

    void start_log_file();
    void update_log_file();
    void close_log_file();
    void display_time(int iteratorStep);
};
