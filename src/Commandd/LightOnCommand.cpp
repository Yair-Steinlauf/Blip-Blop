#include "LightOnCommand.h"

LightOnCommand::LightOnCommand(bool& state) : lightState(state) {}


void LightOnCommand::execute() {
    lightState = true;
    std::cout << "Light turned ON\n";
}

void LightOnCommand::undo() {
    lightState = false;
    std::cout << "Light turned OFF (undo)\n";
}
