#include <iostream>
#include "Sim.h"
#include "Globals.h"
#include "BoardingTypes.h"
#include "InputArguments.h"
#include "error.h"
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main(int numOfArgs, char* argv[]) {
    Global::Globals globalValues;

    path exePath;
    path scenarioPath;
    if(!exists("Outputs")){create_directories("Outputs");} // ensure Outputs path exists

    // find the directory of root directory and the config file. Later this will be a variable config file for differing scenarios
    exePath = absolute(argv[0]).parent_path();
    scenarioPath = exePath  / "Scenarios" / "config.ini";

    // set values, and fail out the sim if no setup file was found
    std::function<seat_pos(int, Global::Globals*)>& boardingType = processInputs(numOfArgs, argv, globalValues, scenarioPath.string());

    // initialize Sim Master
    Sim primeSim(&globalValues, boardingType);
    // primeSim.display_seatPoses(); // This is an early logging method, not for final product
    
    // This starts and runs the sim as it was initialized
    primeSim.run_sim(globalValues.simMaxLength, 2, 0, &globalValues);
    
    // after sim has ended
    primeSim.close_log_file(); 
        return 0;
    }

/*
TODO:
0.  Need to swap the check to check for all people in front while not overloading the sim, with better organized boarding, current is works (thus current implimentation), but for chaotic seating orders, this needs to be addressed.
1.  Unit Tests:
    a. look at the UnitTests file for list
2.  timing changes
    a. change to adaptive step solver
    b. create an "end to sim" check if everyone is seated or if things are truly stuck. This would allow for the sim to understand if there hasn't been movement and save processing time.
3.  redistribute my Sim.cpp file, as its starting to get bloated with functions for output files and input processing.
4.  impliment the type of boarding type change from commandline
    a. DONE!
    b. this will likely require some if statements but I might be able to play something fun with a trig function, will play around with it.
        i. for a real project def just do an if statement to flip a variable from 1 to -1
5.  rework readme to have preliminary results and to have basic compiling/debugging assistance
6.  Boarding Methods
    a. impliment steffan perfect boarding method
    b. fix the boarding methods so that they go outside to middle then outside to middle again
    c. impliment family boarding (ie 3 people in a row, maybe have it be random groups of 1-4)
7.  make more analysis tools, ideally tracking metrics like average velocity, and so on.
    a. primary tool I want is one that says, from time on the plane to time sitting down, how often were they stopped
    b. a tool that shows where in the plane they are stopped on average would be good
    c. a tool that shows calculates the difference between they stopped and their seat position, and summing it across a run would be useful as a scoring method
    d. a tool that counts the number time the length of synced baggaging values
8.  impliment people sitting in the wrong spot and having to get back up
9. impliment more safety rails for bad inputs.
10. fix up visualizer
    a. Need to clean the figure sizing so that it looks better - done
    b. Need to add some sort of visualization showing seating and rows
    c. Need to make it save into a sort of gifs of that way we aren't reliant on a matplotlib figure (my eyes its so bright)
11. Randomness - impliment percentage and absolute randomness
    a. Impiment randomness in passenger considerations
        i. movement speed
        ii. baggage placement time
        iii. passenger size
        iv. incompitence (ie if they get the wrong seat [this is a later addition])
    b. Impliment universal flag for yes or no noise in sim
12. Output Conventions
    a. have it change the output_#.csv name based on the type of run you are doing.
    b. maybe have input values used in the run in the csv for ease of checking and for analysis tools to read.
*/

/*
PSUEDOCODE:
set scenario type
init Main Sim class
set sim length
step through
close out of sim and log
*/