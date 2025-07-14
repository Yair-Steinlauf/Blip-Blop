#include "PlayCommand.h"

PlayCommand::PlayCommand(Controller* controller) : m_controller(controller) {}


void PlayCommand::execute() {
    if (m_controller) {

        m_controller->switchToGamePlay();

    }
}