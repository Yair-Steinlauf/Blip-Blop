#include "PauseScreen.h"
#include "PauseScreen.h"
#include "Controller.h"
#include "GamePlay.h"
#include "DataLoader.h"
#include "MusicManager.h"
#include "Commandd/PlayCommand.h"
#include "Commandd/HelpCommand.h"
#include "Commandd/MusicCommand.h"
#include "Commandd/BackCommand.h"
#include "Commandd/ResumeCommand.h"

PauseScreen::PauseScreen(sf::RenderWindow* window, Controller* controller, GamePlay* gamePlay)
    : BaseScreen(window), m_controller(controller), m_gamePlay(gamePlay)
{
    // טעינת פונט
    m_font = DataLoader::getInstance().getP2Font();

    // יצירת רקע חצי שקוף
    m_overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    m_overlay.setFillColor(sf::Color(0, 0, 0, 30)); // שחור חצי שקוף
    m_overlay.setPosition(0, 0);

    // יצירת כותרת "PAUSED"
    m_pauseTitle.setFont(m_font);
    m_pauseTitle.setString("PAUSED");
    m_pauseTitle.setCharacterSize(48);
    m_pauseTitle.setFillColor(sf::Color::White);
    m_pauseTitle.setStyle(sf::Text::Bold);

    // מרכוז הכותרת
    sf::FloatRect titleBounds = m_pauseTitle.getLocalBounds();
    m_pauseTitle.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    m_pauseTitle.setPosition(SCREEN_WIDTH / 2, 150);

    initializeButtons();
}

void PauseScreen::initializeButtons() {
    m_buttons.clear();

   

    // כפתור Resume
    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<ResumeCommand>(this)
    );
    m_buttons[RESUME].setText("Resume", m_font, 24, sf::Color::White);

    // כפתור Help
    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<HelpCommand>(m_controller)
    );
    m_buttons[HELP].setText("Help", m_font, 24, sf::Color::White);

    // כפתור Music Toggle
    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing * 2),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<MusicToggleCommand>(nullptr) // נטפל בזה ידנית
    );
    updateMusicButtonText();

    //// כפתור Exit
    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing * 3),
        buttonWidth, buttonHeight,
        sf::Color(150, 50, 50), 2.f,        
        std::make_unique<BackCommand>(m_controller)
    );
    m_buttons[EXIT].setText("Exit to Menu", m_font, 24, sf::Color::White);
}

void PauseScreen::updateMusicButtonText() {
    bool musicOn = MusicManager::getInstance().isMusicOn();
    std::string musicText = musicOn ? "Music: ON" : "Music: OFF";
    m_buttons[MUSIC_TOGGLE].setText(musicText, m_font, 24, sf::Color::White);
}

void PauseScreen::update(float deltaTime) {
    // לא מעדכנים את המשחק כשהוא מושהה
}

void PauseScreen::draw() {
    // קודם מציירים את מסך המשחק
    if (m_gamePlay) {
        m_gamePlay->BaseScreen::draw(); // רק הרקע, לא העדכונים
    }

    // מציירים את הרקע החצי שקוף
    m_window->draw(m_overlay);

    // מציירים את הכותרת
    m_window->draw(m_pauseTitle);

    // מציירים את הכפתורים
    for (auto& button : m_buttons) {
        button.draw(*m_window);
    }
}

void PauseScreen::handleInput(const sf::Event& event, float deltaTime) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            resumeGame();
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        m_mousePressed = true;
    }
	if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            float mouseX = static_cast<float>(event.mouseButton.x);
            float mouseY = static_cast<float>(event.mouseButton.y);

            for (auto& button : m_buttons) {
                if (button.isClicked(mouseX, mouseY)) {
                    if (&button == &m_buttons[MUSIC_TOGGLE] && m_mousePressed) {
                        m_mousePressed = false;
                        // טיפול מיוחד בכפתור המוזיקה
                        toggleMusic();
                    }
                    else {
                        button.trigger();
                    }
                    break;
                }
            }
        }
    }

    // הדגשת כפתורים
    if (event.type == sf::Event::MouseMoved) {
        float mouseX = static_cast<float>(event.mouseMove.x);
        float mouseY = static_cast<float>(event.mouseMove.y);

        for (auto& button : m_buttons) {
            button.setHighlight(button.isClicked(mouseX, mouseY));
        }
    }
}

void PauseScreen::resumeGame() {
    if (m_controller) {
        m_controller->resumeFromPause();
    }
}

void PauseScreen::exitToMenu() {
    if (m_controller) {
        m_controller->backCommand();
    }
}

void PauseScreen::toggleMusic() {
    MusicManager::getInstance().toggleMusic();
    updateMusicButtonText();
}

void PauseScreen::showHelp() {
    if (m_controller) {
        m_controller->switchToHelp();
    }
}