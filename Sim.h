#include <iostream>
#include <vector>

class Sim {
private:
    int passengerCount{1};
    int nPsngr{0};
    bool simEnd = false;
    std::vector<int> xPos;
    std::vector<int> yPos;
    std::vector<int> moveSpeed;
    std::vector<int> xSeatPos;
    std::vector<int> ySeatPos;
    std::vector<int> id;
    std::vector<bool> seated;
    void move(int person);
public:
    Sim(int passengerCount);
    void step();
    
    //display
    void display_pos(int person)
    {
        std::cout  << '(' << xPos[person] << ',' << yPos[person] << ')' << std::endl;
    };

    // getters
    int get_xPos(int person){return xPos[person];};
    int get_yPos(int person){return yPos[person];};
    int get_xSeatPos(int person){return xSeatPos[person];};
    int get_ySeatPos(int person){return ySeatPos[person];};
    int get_newSpeed(int person){return moveSpeed[person];};
    int get_id(int person){return id[person];};


    // setters
    void set_xPos(int newPos, int person){xPos[person] = newPos;};
    void set_yPos(int newPos, int person){yPos[person] = newPos;};
    void set_xSeatPos(int newPos, int person){xSeatPos[person] = newPos;};
    void set_ySeatPos(int newPos, int person){ySeatPos[person] = newPos;};
    void set_newSpeed(int newSpeed, int person){moveSpeed[person] = newSpeed;};
    void set_id(int newId, int person){xPos[person] = newId;};
    
};
