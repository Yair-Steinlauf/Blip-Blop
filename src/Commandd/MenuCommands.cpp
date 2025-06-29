#include "MenuCommands.h"
#include "MenuScreen.h"
#include "Controller.h"
#include <iostream>

void PlayCommand::execute() {
    if (m_controller) {
        m_controller->switchToGamePlay();
    }
}

void HelpCommand::execute() {
    if (m_menuScreen) {
        m_menuScreen->showHelp();
    }
}

void ExitCommand::execute() {
    if (m_menuScreen) {
        m_menuScreen->exitGame();
    }
}