#include "init_types.h"
#include <bits/stdc++.h>
#include <iostream>

seat_pos fullColumn(int person, int planeLength){
    seat_pos output = {static_cast<float>(person / planeLength), static_cast<float>(person % planeLength)};
    output.xSeatPos += static_cast<int>(output.xSeatPos >= 3); // 3 is a magic number for down the middle of the plane. Could make this adjustable
    return output;
}

seat_pos spacedColumn(int person, int planeLength){
    seat_pos output = {0.0, 0.0};
    output.xSeatPos = static_cast<float>(person * 2 / planeLength);
    if ( (static_cast<int>(output.xSeatPos) % 2) == 0 ) {
        output.ySeatPos  = std::round(person * 2 % planeLength); 
    } else {
        output.ySeatPos  = std::round(person * 2 % planeLength + 1); 
        output.xSeatPos -= 1;   
    }
    output.xSeatPos += static_cast<int>(output.xSeatPos >= 3); // 3 is a magic number for down the middle of the plane. Could make this adjustable
    return output;
}