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
    GameOverCommand(Controller* controller, GameOverScreen::GameResult result, int score);
        

    void execute() override;
};