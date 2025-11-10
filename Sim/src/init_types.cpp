#include <bits/stdc++.h>
#include <iostream>
#include "init_types.h"
#include "Globals.h"

seat_pos fullColumn(int person, int planeLength, Global::Globals* globalValues){
    seat_pos output = {static_cast<float>(person / planeLength), static_cast<float>(person % planeLength) + 1};
    output.xSeatPos += static_cast<int>(output.xSeatPos >= globalValues->planeMidPoint);
    return output;
}

seat_pos spacedColumn(int person, int planeLength, Global::Globals* globalValues){
    seat_pos output = {0.0, 0.0};
    output.xSeatPos = static_cast<float>(person * 2 / planeLength);
    if ( (static_cast<int>(output.xSeatPos) % 2) == 0 ) {
        output.ySeatPos  = std::round(person * 2 % planeLength) + 1; 
    } else {
        output.ySeatPos  = std::round(person * 2 % planeLength + 1); 
        output.xSeatPos -= 1;   
    }
    output.xSeatPos += static_cast<int>(output.xSeatPos >= globalValues->planeMidPoint);
    return output;
}