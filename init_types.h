#include <iostream>

/*
GOAL:
1. Define the basic seat mapping I want with variable number of individuals. Probably make it a function rather than hard code positions out.
2. Define Uncertainty function that can shift values by small amounts
3. Define Random function that will give truly random centers to values
4. combine both 2 and 3 into 1 for grabbing speed of people and size
*/
struct seat_pos{
    float xSeatPos;
    float ySeatPos;
};

seat_pos fullColumn(int person, int planeLength); 
seat_pos spacedColumn(int person, int planeLength);
