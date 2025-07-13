#pragma once

#include <iostream>
#include "Command.h"
#include "UndoableCommand.h"

class LightOnCommand : public UndoableCommand {
private:
    bool& lightState;

public:
    LightOnCommand(bool& state);

    void execute() override;
    void undo() override;
};
