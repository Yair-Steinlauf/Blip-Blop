#include "MenuScreen.h"
#include "ScreensFactory.h"
#include "DataLoader.h"


#include "Controller.h"
#include <iostream>
#include "MusicCommand.h"  
#include "MusicManager.h"
#include <HelpCommand.h>
#include <PlayCommand.h>
#include <ExitCommand.h>

// רישום MenuScreen בפקטורי
static auto registerMenuScreen = ScreenFactory::instance().registerType(
    ObjectType::MenuScreen,
    [](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen> {
        return std::make_unique<MenuScreen>(window);
    }
);


MenuScreen::MenuScreen(sf::RenderWindow* window, Controller* controller)
    : BaseScreen(window), m_controller(controller) {

    // טעינת רקע
    m_background.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MenuBackground));

    // יצירת פונט
    const int textSize = 35;
    m_font = DataLoader::getP2Font();
    m_title.setFont(m_font);
    m_title.setString("GAME MENU");
    m_title.setCharacterSize(48);
    m_title.setFillColor(sf::Color::Yellow);

    // מיקום הכותרת במרכז העליון
    m_titleBounds = m_title.getLocalBounds();
    m_title.setOrigin(m_titleBounds.width / 2, m_titleBounds.height / 2);
    m_title.setPosition(SCREEN_WIDTH / 2.0f, 100.0f);
    // חישוב מיקומים למרכז המסך
    

    // כפתור Play
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY),
        buttonWidth, buttonHeight,
        sf::Color::Green,
        3.0f,
        std::make_unique<PlayCommand>(m_controller)
    );
    m_buttons.back().setText("PLAY", m_font, textSize, sf::Color::Black);

    // כפתור Help
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY + buttonSpacing),
        buttonWidth, buttonHeight,
        sf::Color::Blue,
        3.0f,
        std::make_unique<HelpCommand>(m_controller)  
    );
    m_buttons.back().setText("HELP", m_font, textSize, sf::Color::Black);

    // כפתור Music (חדש!)
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY + 2 * buttonSpacing),
        buttonWidth, buttonHeight,
        sf::Color(150, 100, 0, 255), // כתום
        3.0f,
        std::make_unique<MusicToggleCommand>(this)
    );
    m_buttons.back().setOutlineColor(sf::Color::Black);

    // כפתור Exit
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY + 3 * buttonSpacing),
        buttonWidth, buttonHeight,
        sf::Color::Red,
        3.0f,
        std::make_unique<ExitCommand>(this)
    );
    m_buttons.back().setText("EXIT", m_font, textSize, sf::Color::Black);
    
    updateMusicButtonText();
    MusicManager::getInstance().startBackgroundMusic();
}
void MenuScreen::updateMusicButtonText() {
    if (m_buttons.size() >= 3) {
        std::string musicText = MusicManager::getInstance().isMusicOn() ? "MUSIC: ON" : "MUSIC: OFF";
        m_buttons[2].setText(musicText, DataLoader::getP2Font(), 24, sf::Color::White);  // כפתור המוזיקה הוא השלישי
    }
}

void MenuScreen::toggleMusic() {
    MusicManager::getInstance().toggleMusic();
    updateMusicButtonText();
}

void MenuScreen::update(float deltaTime) {
    // עדכון כפתורים אם יש צורך
    for (auto& button : m_buttons) {
        // כאן אפשר להוסיף אנימציות או לוגיקה נוספת
    }
}

void MenuScreen::draw() {
    BaseScreen::draw();  // מצייר את הרקע

    // ציור כפתורים
    for (const auto& button : m_buttons) {
        button.draw(*m_window);
    }           

    m_window->draw(m_title);
}

void MenuScreen::handleInput(const sf::Event& event, float deltaTime) {
    if (event.type == sf::Event::MouseButtonPressed) {
        m_mousePressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            float mouseX = static_cast<float>(event.mouseButton.x);
            float mouseY = static_cast<float>(event.mouseButton.y);
			if(m_mousePressed)
            {
                m_mousePressed = false;
                // בדיקה איזה כפתור נלחץ
                for (auto& button : m_buttons) {
                    if (button.isClicked(mouseX, mouseY)) {
                        button.trigger();  // הפעלת הפקודה של הכפתור
                        break;
                    }
                }
            }
        }
    }

    // עדכון highlight של כפתורים
    if (event.type == sf::Event::MouseMoved) {
        float mouseX = static_cast<float>(event.mouseMove.x);
        float mouseY = static_cast<float>(event.mouseMove.y);

        for (auto& button : m_buttons) {
            button.setHighlight(button.isClicked(mouseX, mouseY));
        }
    }
}

void MenuScreen::showHelp() {
    std::cout << "HELP - Game Controls:" << std::endl;
    std::cout << "A/D - Move left/right" << std::endl;
    std::cout << "Space - Jump" << std::endl;
    std::cout << "Mouse - Aim and shoot" << std::endl;
    std::cout << "Collect gifts to upgrade your weapon!" << std::endl;
}

void MenuScreen::exitGame() {
    std::cout << "Exiting game..." << std::endl;
    m_window->close();
}