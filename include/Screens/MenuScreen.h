#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <vector>

// Forward declarations
class Controller;

class MenuScreen : public BaseScreen {
public:
    MenuScreen(sf::RenderWindow* window, Controller* controller = nullptr);
    ~MenuScreen() override = default;

    void update(float deltaTime) override;
    void draw() override;
    void handleInput(const sf::Event& event, float deltaTime) override;

    // פונקציות לטיפול בפקודות הכפתורים
    void showHelp();
    void exitGame();
    void toggleMusic();

private:
    std::vector<Button> m_buttons;
    Controller* m_controller;
    void updateMusicButtonText();
    bool m_mousePressed = false;           // זוכר אם העכבר לחוץ    
};