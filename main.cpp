#include <iostream>
#include "Sim.h"

int main() {
    Sim primeSim(48);
    primeSim.display_seatPoses();
    
    // for (int i = 0;  i < 12; i++){
    //     std::cout << "Time: " << i << std::endl;
    //     for (int j = 0; j < primeSim.lenPassengerList; j++){
    //         std::cout << "Person " << j+1 << " is at ";
    //         primeSim.display_pos(j);
    //     }
    //     primeSim.step();
    // }
    return 0;
}

/*
TODO:
0. Impliment seperate "in the way" function that splits between x and y, have this inserted in the code where the logic block is for each. might be cumbersome given the direction differences present.
1. Impliment sequencing for passengers
    a. Will want a general function call that reads a datastructure or sub function that sets the passengers in sequence
2. Change displaying to terminal so that instead it writes it all to a log file
3. Stopping for Baggage time, I am thinking adding some sort of timer to the passengers
    a. so to have varying movement times, could do it instead as a count down from 10, and with varying speeds it deletes it until its zero, and once its zero, allow movement through baggage lane
4. change up movements so that they allow more fractional movement and variation between passengers
5. Make a python tool to read output of 2. to allow it to do analysis on various passengers to try and find root cause of slow downs and speed ups
6. Far Off: Impliment a visualization for the passenger positions and allow for a cool animation
7. Maybe have a swapable feature from move and move recursive, because I believe the recursive method would be slow than the standard method, if easier to work with and read.
*/

/*
PSUEDOCODE:
set scenario type
init Main Sim class
set sim length
step through
*/