#pragma once
#include "Command.h"
#include "GameOverScreen.h"

class Controller;

class GameOverCommand : public Command {
private:
    Controller* m_controller;
    GameOverScreen::GameResult m_result;
    int m_score;

public:
    GameOverCommand(Controller* controller, GameOverScreen::GameResult result, int score)
        : m_controller(controller), m_result(result), m_score(score) {
    }

    void execute() override;
};