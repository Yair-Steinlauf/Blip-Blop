#include "LightOnCommand.h"

LightOnCommand::LightOnCommand(bool& state) : lightState(state) {}


void LightOnCommand::execute() {
    lightState = true;
}

void LightOnCommand::undo() {
    lightState = false;
}
