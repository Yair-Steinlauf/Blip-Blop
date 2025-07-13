#include "MusicCommand.h"
#include "MenuScreen.h"
#include "MusicManager.h"

MusicToggleCommand::MusicToggleCommand(MenuScreen* menuScreen) : m_menuScreen(menuScreen) {}


void MusicToggleCommand::execute() {
    if (m_menuScreen) {
        m_menuScreen->toggleMusic();
    }
}