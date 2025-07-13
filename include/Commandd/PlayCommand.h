#pragma once
#include "Command.h"
#include "Controller.h"
#include <iostream>


class PlayCommand : public Command {
private:
    Controller* m_controller;

public:
    PlayCommand(Controller* controller);

    void execute() override;
};