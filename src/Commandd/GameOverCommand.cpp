#include "GameOverCommand.h"
#include "Controller.h"

void GameOverCommand::execute() {
    if (m_controller) {
        m_controller->switchToGameOver(m_result, m_score);
    }
}