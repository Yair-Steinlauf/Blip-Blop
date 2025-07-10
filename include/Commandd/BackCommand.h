#pragma once
#include "Command.h"
#include "Controller.h"


class BackCommand : public Command {
private:
    Controller* m_controller;

public:
    BackCommand(Controller* controller) : m_controller(controller) {}
    void execute() override;
};