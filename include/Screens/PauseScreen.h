#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <memory>
#include <vector>
#include "Constance.h"


class Controller;
class GamePlay;

class PauseScreen : public BaseScreen {
public:
    PauseScreen(sf::RenderWindow* window, Controller* controller, GamePlay* gamePlay);
    ~PauseScreen() override = default;

    void update(float deltaTime) override;
    void draw() override;
    void handleInput(const sf::Event& event, float deltaTime) override;

    void resumeGame();
    void exitToMenu();
    void toggleMusic();
    void showHelp();

private:
    void initializeButtons();
    void updateMusicButtonText();

    Controller* m_controller;
    GamePlay* m_gamePlay;
    std::vector<Button> m_buttons;
    sf::RectangleShape m_overlay; // חצי שקוף מעל המשחק
    sf::Text m_pauseTitle;
    sf::Font m_font;
    bool m_mousePressed = false;           // זוכר אם העכבר לחוץ    
    enum ButtonIndex {
        RESUME = 0,
        PLAY_AGAIN = 1,
        HELP = 2,
        MUSIC_TOGGLE = 3,
        EXIT = 4
    };


    const float buttonWidth = 200;
    const float buttonHeight = 50;
    const float startY = 200;
    const float spacing = 70;
    float centerX = SCREEN_WIDTH / 2 - buttonWidth / 2;
};