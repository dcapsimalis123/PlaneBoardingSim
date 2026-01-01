#include <iostream>
#include "init_types.h"
#include "Globals.h"

seat_pos fullColumn(int person, Global::Globals* globalValues){
    seat_pos output = {static_cast<float>(person / globalValues->planeLength), static_cast<float>(person %globalValues-> planeLength) + 1};
    output.xSeatPos += static_cast<int>(output.xSeatPos >= globalValues->planeMidPoint);
    return output;
}

seat_pos spacedColumn(int person, Global::Globals* globalValues){
    seat_pos output = {0.0, 0.0};
    output.xSeatPos = static_cast<float>(person * 2 / globalValues->planeLength);
    if ( (static_cast<int>(output.xSeatPos) % 2) == 0 ) {
        output.ySeatPos  = std::round(person * 2 % globalValues->planeLength) + 1; 
    } else {
        output.ySeatPos  = std::round(person * 2 % globalValues->planeLength + 1); 
        output.xSeatPos -= 1;   
    }
    output.xSeatPos += static_cast<int>(output.xSeatPos >= globalValues->planeMidPoint);
    return output;
}

seat_pos fullColumnReversed(int person, Global::Globals* globalValues){
    seat_pos output = fullColumn(person, globalValues);
    output.ySeatPos = globalValues->planeLength - output.ySeatPos; 
    return output;
}

seat_pos spacedColumnReversed(int person, Global::Globals* globalValues){
    seat_pos output = spacedColumn(person, globalValues);
    output.ySeatPos = globalValues->planeLength-  output.ySeatPos;
    return output;
}