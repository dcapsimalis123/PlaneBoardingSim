#include <iostream>
#include "Globals.h"
#include "BoardingTypes.h"
#include <functional>

int read_input_file(Global::Globals& globalValues, std::string pathToInput);
std::function<seat_pos(int, Global::Globals*)>& processInputs(int argc, char* argv[], Global::Globals& globalValues, std::string rootDirectory);