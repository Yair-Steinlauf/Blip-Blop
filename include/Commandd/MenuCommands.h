#pragma once
#include "Command.h"

// Forward declaration
class MenuScreen;
class Controller;

// ����� ������ Play
class PlayCommand : public Command {
private:
    Controller* m_controller;

public:
    PlayCommand(Controller* controller) : m_controller(controller) {}

    void execute() override;
};

// ����� ������ Help
class HelpCommand : public Command {
private:
    MenuScreen* m_menuScreen;

public:
    HelpCommand(MenuScreen* menuScreen) : m_menuScreen(menuScreen) {}

    void execute() override;
};

// ����� ������ Exit
class ExitCommand : public Command {
private:
    MenuScreen* m_menuScreen;

public:
    ExitCommand(MenuScreen* menuScreen) : m_menuScreen(menuScreen) {}

    void execute() override;
};