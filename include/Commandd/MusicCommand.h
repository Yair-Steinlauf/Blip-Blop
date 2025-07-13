#pragma once
#include "Command.h"

class MenuScreen;

class MusicToggleCommand : public Command {
private:
    MenuScreen* m_menuScreen;

public:
    MusicToggleCommand(MenuScreen* menuScreen);

    void execute() override;
};