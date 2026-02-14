#include <iostream>
#include <string>
#include <stdexcept>
#include "InputArguments.h"
#include "BoardingTypes.h"
#include <functional>
#include <fstream>
#include <algorithm>
#include <format>
#include <filesystem>

std::string find_data(std::string inputLine){
    // takes the line out of a config file and returns just the input value. This is processed into an int or other data type later.
    int pos = inputLine.find(':'); // update this with a method to string oout all spaces after the semi colon but for now just make it robust out to one whitespace
    while(true){
        if(inputLine.substr(pos+1,1) == " "){ 
            pos++;
        }else{
            break;
        }
    }
    return inputLine.substr(pos);
}

int read_input_file(Global::Globals& globalValues, std::string pathToInput){
    //  This file takes in the ini and reads its values directly into the globals
    //  TODO: This is hardcoded and needs to be made 
    std::ifstream settingsFile;
    settingsFile.open(pathToInput, std::ifstream::in);

    if (!settingsFile) {
        std::cout << "Unable to open settings file" << std::endl;
        return -1;
    }

    std::string curLine; // TODO: This block should be a single function call. Also should be detecting the name of the variable in the line and assign that to the value listed. Hardcoded for now.
    getline(settingsFile, curLine);
    globalValues.planeWidth = std::stoi(find_data(curLine));
    getline(settingsFile, curLine);
    globalValues.planeMidPoint = std::stoi(find_data(curLine));
    getline(settingsFile, curLine);
    globalValues.planeLength = std::stoi(find_data(curLine));
    getline(settingsFile, curLine);
    globalValues.timeStepLength = std::stoi(find_data(curLine));
    getline(settingsFile, curLine);
    globalValues.simMaxLength = std::stoi(find_data(curLine));
    getline(settingsFile, curLine);
    globalValues.passengerCount = std::stoi(find_data(curLine));

    return 0;
}

int processInputs(int argc, char* argv[], Global::Globals& globalValues, std::string scenarioFile){
    // This file takes sets global variables according to inputs given from user.
    // first it sets all globals to the values in the ini file selected (using Default if none given), then it sets globals from the cmd line arguments.
    // TODO: Impliment feature for selecting ini and for defaulting
    std::cout << "Processing Arguments" << std::endl;
    if(read_input_file(globalValues, scenarioFile) == -1){
        return -1;
    };

    int globalValueNum = 6;
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
                    globalValues.planeWidth     = std::stoi(argv[++i]);
                    varHash[0] = 1;
                    break;
                case 'm': // mid aisle
                    globalValues.planeMidPoint  = std::stoi(argv[++i]);
                    varHash[1] = 1;
                    break;
                case 'l': // plane length
                    globalValues.planeLength    = std::stoi(argv[++i]);
                    varHash[2] = 1;
                    break;
                case 't': // changing the individual step timing
                    globalValues.timeStepLength = std::stoi(argv[++i]);
                    varHash[3] = 1;
                    break;
                case 's': // max length of sim
                    globalValues.simMaxLength   = std::stoi(argv[++i]);
                    varHash[4] = 1;
                    break;
                case 'p': // Number of passengers
                    globalValues.passengerCount = std::stoi(argv[++i]);
                    varHash[5] = 1;
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
    // TODO: reimpliment a different version of default values from outside config file, or move error of no config file to inside this function.
}