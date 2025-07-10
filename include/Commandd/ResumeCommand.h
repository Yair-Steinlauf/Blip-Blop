// ResumeCommand.h
#pragma once
#include "Command.h"

class PauseScreen;

class ResumeCommand : public Command {
private:
    PauseScreen* m_pauseScreen;

public:
    ResumeCommand(PauseScreen* pauseScreen);
    void execute() override;
};


