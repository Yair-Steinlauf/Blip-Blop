#pragma once
#include "Command.h"
#include "MenuScreen.h"

// ����� ������ Exit
class ExitCommand : public Command {
private:
    MenuScreen* m_menuScreen;

public:
    ExitCommand(MenuScreen* menuScreen) : m_menuScreen(menuScreen) {}

    void execute() override;
};