#include "ExitCommand.h"

void ExitCommand::execute() {
    if (m_menuScreen) {
        m_menuScreen->exitGame();
    }
}