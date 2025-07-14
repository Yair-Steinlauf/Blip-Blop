#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <vector>
#include "Constance.h"

// Forward declarations
class Controller;

class HelpScreen : public BaseScreen {
public:
    HelpScreen(sf::RenderWindow* window, Controller* controller = nullptr);
    ~HelpScreen() override = default;

    void update(float deltaTime) override;
    void draw() override;
    void drawComponent();
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
    const float scrollAreaTop = 120.0f;
    const float scrollAreaHeight = SCREEN_HEIGHT - 160.0f;
    const float scrollBarHeight = 200.0f;
    const float scrollBarWidth = 8.0f;
    const float scrollBarX = SCREEN_WIDTH - 20.0f;
    const float scrollBarY = 140.0f;
    // ציור טקסט העזרה עם גלילה
    const float startY = 30.0f; // התחלה יחסית לאזור הגלילה
    const float lineSpacing = 25.0f;
    // טקסט העזרה
    std::vector<std::string> m_helpText;
    sf::Text m_title;
    sf::FloatRect m_titleBounds;
    sf::Text m_scrollInstructions;
    sf::FloatRect m_instrBounds;
    sf::RectangleShape m_scrollBarBg;
    sf::RectangleShape m_scrollHandle;



    void initializeHelpText();
    void updateScrollLimits();
};