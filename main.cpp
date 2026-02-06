#include <iostream>
#include "Sim\include\Sim.h"
#include "Sim\include\Globals.h"
#include "Sim\include\BoardingTypes.h"
#include "Sim\include\InputArguments.h"

int main(int numOfArgs, char* argv[]) {
    Global::Globals globalValues;
    
    processInputs(numOfArgs, argv, &globalValues);

    
    Sim primeSim(&globalValues, &fullColumnReversed);
    primeSim.display_seatPoses();
    
    primeSim.run_sim(globalValues.simMaxLength, 2, 0, &globalValues);
    primeSim.close_log_file();
    return 0;
}

/*
TODO:
0. Need to swap the check to check for all people in front while not overloading the sim, with better organized boarding, current is works (thus current implimentation), but for chaotic seating orders, this needs to be addressed.
1. Unit Tests:
    a. stepping into plane sequencing
    b. stopping at center aisle
    c. stopping at seat row
    d. baggage placing takes x amount of time based on speed
    e. passing check (ie if someone isn't moving, make sure people behind them don't pass them)
    f. check it at each section (3) and then at turning points for each
2. timing changes
    a. change to adaptive step solver
    b. create an "end to sim" check if everyone is seated or if things are truly stuck. This would allow for the sim to understand if there hasn't been movement and save processing time.
3. Far Off: Impliment a visualization for the passenger positions and allow for a cool animation
    a. okay so I jumped the gun on this one =D
    b. Need to clean the figure sizing so that it looks better
    c. Need to add some sort of visualization showing seating and rows
*/

/*
PSUEDOCODE:
set scenario type
init Main Sim class
set sim length
step through
*/