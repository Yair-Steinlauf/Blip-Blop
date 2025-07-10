#include "PlayCommand.h"

void PlayCommand::execute() {
    if (m_controller) {
        m_controller->switchToGamePlay();
    }
}