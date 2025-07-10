#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <vector>

// Forward declarations
class Controller;

class HelpScreen : public BaseScreen {
public:
    HelpScreen(sf::RenderWindow* window, Controller* controller = nullptr);
    ~HelpScreen() override = default;

    void update(float deltaTime) override;
    void draw() override;
    void handleInput(const sf::Event& event, float deltaTime) override;

    void backButton();

private:
    std::vector<Button> m_buttons;
    Controller* m_controller;
    sf::Font m_font;
    bool m_fontLoaded = false;

    // משתנים לגלילה
    float m_scrollOffset = 0.0f;
    float m_maxScrollOffset = 0.0f;
    const float m_scrollSpeed = 30.0f;

    // טקסט העזרה
    std::vector<std::string> m_helpText;
    void initializeHelpText();
    void updateScrollLimits();
};