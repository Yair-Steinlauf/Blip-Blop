#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <memory>
#include <vector>

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
        HELP = 1,
        MUSIC_TOGGLE = 2,
        EXIT = 3
    };
};