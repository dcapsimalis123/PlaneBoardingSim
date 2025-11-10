#include <iostream>
#include <vector>

class Person
{
private:

public:
    std::vector<float> positionVector;
    float moveSpeed;
    float xSeatPos;
    float ySeatPos;
    float baggageSpeed; // speed of placing baggage, should be understood as a percentage of time to completion, which is 1.0
    float baggageCompletion; // float for completion of baggage placement, 1.0 is complete
    int   id;
    bool  seated;
//Constructor
    Person(int id, float txSeatPos, float tySeatPos);

    //setter
    void baggage_placement_step(float* remainingTime);

    //Destructor
    ~Person();

    //display
    void display_pos(){std::cout  << '(' << positionVector[0] << ',' << positionVector[1] << ')' << std::endl;};
    void display_seatPos(){std::cout  << '(' << xSeatPos << ',' << ySeatPos << ')' << std::endl;};
    
    // setter 
    void seated_check(){if(positionVector[0] == xSeatPos && positionVector[1] == ySeatPos){seated = true;}}

};