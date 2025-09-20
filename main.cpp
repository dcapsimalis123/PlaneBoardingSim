#include <iostream>
#include "Sim.h"

int main() {
    Sim primeSim(2);
    for (int i = 0; i++; i < 12){
        primeSim.display_pos(0);
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