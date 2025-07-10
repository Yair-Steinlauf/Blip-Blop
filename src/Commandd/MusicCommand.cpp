#include "MusicCommand.h"
#include "MenuScreen.h"
#include "MusicManager.h"

void MusicToggleCommand::execute() {
    if (m_menuScreen) {
        m_menuScreen->toggleMusic();
    }
}