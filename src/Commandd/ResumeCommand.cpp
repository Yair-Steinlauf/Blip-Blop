
#include "ResumeCommand.h"
#include "PauseScreen.h"

ResumeCommand::ResumeCommand(PauseScreen* pauseScreen) : m_pauseScreen(pauseScreen)
{
}

void ResumeCommand::execute() {
    if (m_pauseScreen) {
        m_pauseScreen->resumeGame();
    }
}