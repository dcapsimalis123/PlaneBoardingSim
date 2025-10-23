#include <iostream>
#include <vector>

class Person
{
private:

public:
    std::vector <float> posVec;
    float moveSpeed;
    float xSeatPos;
    float ySeatPos;
    int   id;
    bool  seated;
//Constructor
    Person(int id, float txSeatPos, float tySeatPos);

    //Destructor
    ~Person();

    //display
    void display_pos(){std::cout  << '(' << posVec[0] << ',' << posVec[1] << ')' << std::endl;};
    void display_seatPos(){std::cout  << '(' << xSeatPos << ',' << ySeatPos << ')' << std::endl;};
    
    // setter 
    void seated_check(){if(posVec[0] == xSeatPos and posVec[1] == ySeatPos){seated = true;}}

};