#include <iostream>
#include <vector>

class Person
{
private:

public:
    float xPos;
    float yPos;
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
    void display_pos()const{std::cout  << '(' << xPos << ',' << yPos << ')' << std::endl;};
    void display_seatPos()const{std::cout  << '(' << xSeatPos << ',' << ySeatPos << ')' << std::endl;};

};