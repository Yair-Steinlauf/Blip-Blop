#pragma once
#include "Command.h"
#include "Controller.h"
#include <iostream>


class PlayCommand : public Command {
private:
    Controller* m_controller;

public:
    PlayCommand(Controller* controller) : m_controller(controller) {}

    void execute() override;
};