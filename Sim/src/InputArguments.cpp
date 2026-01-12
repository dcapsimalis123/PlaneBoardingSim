#include <iostream>
#include <string>
#include <stdexcept>
#include "InputArguments.h"


void processInputs(int argc, char* argv[], Global::Globals* globalValues){
    std::cout << "Processing Arguments" << std::endl;
    int globalValueNum = 4;
    int varHash[globalValueNum] = {0,0,0}; // width = 0, mid point = 1, length = 2, time step length = 3, boarding type = 4
    for (int i = 1; i < argc; ++i) { // start at 1: argv[0] is program name
        if (!argv[i] || argv[i][0] != '-' || !argv[i][1]) continue;
        char opt = argv[i][1];
        if (i + 1 >= argc) {
            std::cout << "missing value for -" << opt << '\n';
            continue;
        }
        try {
            switch (opt) {
                case 'w': // plane width
                    globalValues->planeWidth = std::stoi(argv[++i]);
                    varHash[0] = 1;
                    break;
                case 'm': // mid aisle
                    globalValues->planeMidPoint = std::stoi(argv[++i]);
                    varHash[1] = 1;
                    break;
                case 'l': // plane length
                    globalValues->planeLength = std::stoi(argv[++i]);
                    varHash[2] = 1;
                    break;
                case 't':
                    globalValues->timeStepLength = std::stoi(argv[++i]);
                    varHash[3] = 1;
                    break;
                default:
                    std::cout << "unknown option -" << opt << '\n';
                    break;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "invalid value for -" << opt << "; keeping default\n";
        } catch (const std::out_of_range& e) {
            std::cout << "value out of range for -" << opt << "; keeping default\n";
        } catch (const std::exception& e) {
            std::cout << "error parsing -" << opt << ": " << e.what() << '\n';
        }
    }
    for (int i = 0; i < globalValueNum; ++i){ //default value read in. for now its magic numbers, will correct later.
        if (varHash[i] == 0){
            switch (i)
            {
            case 0:
                globalValues->planeWidth = 5; //default
                break;
            case 1:
                globalValues->planeMidPoint = 3; //default
            case 2:
                globalValues->planeLength = 8; //default
            case 3:
                globalValues->timeStepLength = 1.0f; //default
            default:
                break;
            }
        }
    }
}