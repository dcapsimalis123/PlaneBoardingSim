#include <iostream>
#include "Sim.h"

int main() {
    Sim primeSim(2);
    std::cout << "What" << std::endl;
    for (int i = 0;  i < 12; i++){
        std::cout << "Time: " << i << std::endl;
        std::cout << "Person " <<  "1" << " is at ";
        primeSim.display_pos(0);
        std::cout << "Person " <<  "2" << " is at ";
        primeSim.display_pos(1);
        primeSim.step();
    }
    return 0;
}

/*
PSUEDOCODE:
set scenario type
init Main Sim class
set sim length
step through
*/