#pragma once
#include "Command.h"
#include "Controller.h"
#include <iostream>


class HelpCommand : public Command {
private:
    Controller* m_controller;

public:
    HelpCommand(Controller* controller) : m_controller(controller) {}

    void execute() override;
};