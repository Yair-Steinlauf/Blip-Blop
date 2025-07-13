#include "GameOverCommand.h"
#include "Controller.h"

GameOverCommand::GameOverCommand(Controller* controller, GameOverScreen::GameResult result, int score) : m_controller(controller), m_result(result), m_score(score) {
}


void GameOverCommand::execute() {
    if (m_controller) {
        m_controller->switchToGameOver(m_result, m_score);
    }
}