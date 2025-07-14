#pragma once
#include "Command.h"
#include "Controller.h"


class ExitCommand : public Command {
private:
    Controller* m_controller;


public:
    ExitCommand(Controller* controller);

    void execute() override;
};