#ifndef GLOBALS
#define GLOBALS
namespace Global{  // I think this counts as forward defining?
    struct  Globals{
        int   planeWidth;     // overall width of the plane (technically the left edge people can reach, might want to change that with a size of person variable)
        int   planeMidPoint;  // Where the center aisle will be located right edge of 
        int   planeLength;
        float timeStepLength; // going to integrate a new version of methods for timing to allow for more interesting integration methods
    };
}
#endif