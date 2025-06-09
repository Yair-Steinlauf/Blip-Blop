#pragma once
#include "Command.h"

class UndoableCommand : public Command {
public:
    virtual void undo() = 0;
};
