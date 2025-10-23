#include <iostream>
#include "Sim.h"

int main() {
    Sim primeSim(48);
    primeSim.display_seatPoses();
    
    primeSim.run_sim(100,2,0);
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
*/

/*
PSUEDOCODE:
set scenario type
init Main Sim class
set sim length
step through
*/