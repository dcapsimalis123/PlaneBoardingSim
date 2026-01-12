#include <iostream>
#include "Sim\include\Sim.h"
#include "Sim\include\Globals.h"
#include "Sim\include\BoardingTypes.h"
#include "Sim\include\InputArguments.h"

int main(int numOfArgs, char* argv[]) {
    Global::Globals globalValues;
    
    processInputs(numOfArgs, argv, &globalValues);

    Sim primeSim(2, &globalValues, &fullColumn);
    primeSim.display_seatPoses();
    
    primeSim.run_sim(10,2,0, &globalValues);
    primeSim.close_log_file();
    return 0;
}

/*
TODO:
0. Need to swap the check to check for all people in front while not overloading the sim, with better organized boarding, current is works (thus current implimentation), but for chaotic seating orders, this needs to be addressed.
1. Impliment sequencing for passengers
    a. Will want a general function call that reads a datastructure or sub function that sets the passengers in sequence
    b. *** need to impliment back to front loading, to do so I need to fill the magic numbers with values (ie plane length, plane width, etc.)
2. Change displaying to terminal so that instead it writes it all to a log file
3. Stopping for Baggage time, I am thinking adding some sort of timer to the passengers
    a. so to have varying movement times, could do it instead as a count down from 10, and with varying speeds it deletes it until its zero, and once its zero, allow movement through baggage lane
4. Make a python tool to read output of 2. to allow it to do analysis on various passengers to try and find root cause of slow downs and speed ups
5. Far Off: Impliment a visualization for the passenger positions and allow for a cool animation
6. Unit Tests:
    1. stepping into plane sequencing
    2. stopping at center aisle
    3. stopping at seat row
    4. baggage placing takes x amount of time based on speed
    5. passing check (ie if someone isn't moving, make sure people behind them don't pass them)
        a. check it at each section (3) and then at turning points for each
*/

/*
PSUEDOCODE:
set scenario type
init Main Sim class
set sim length
step through
*/