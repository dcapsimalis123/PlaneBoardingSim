#include <iostream>
#include "Sim.h"

int main() {
    Sim primeSim(20);
    std::cout << "What" << std::endl;
    for (int i = 0;  i < 12; i++){
        std::cout << "Time: " << i << std::endl;
        for (int j = 0; j < primeSim.lenPassengerList; j++){
            std::cout << "Person " << j+1 << " is at ";
            primeSim.display_pos(j);
        }
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