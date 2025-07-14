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
#include <ExitCommand.h>

PauseScreen::PauseScreen(sf::RenderWindow* window, Controller* controller, GamePlay* gamePlay)
    : BaseScreen(window), m_controller(controller), m_gamePlay(gamePlay)
{

    m_font = DataLoader::getInstance().getP2Font();


    m_overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    m_overlay.setFillColor(sf::Color(0, 0, 0, 30));
    m_overlay.setPosition(0, 0);


    m_pauseTitle.setFont(m_font);
    m_pauseTitle.setString("PAUSED");
    m_pauseTitle.setCharacterSize(48);
    m_pauseTitle.setFillColor(sf::Color::White);
    m_pauseTitle.setStyle(sf::Text::Bold);


    sf::FloatRect titleBounds = m_pauseTitle.getLocalBounds();
    m_pauseTitle.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    m_pauseTitle.setPosition(SCREEN_WIDTH / 2, 100);

    initializeButtons();
}

void PauseScreen::initializeButtons() {
    m_buttons.clear();

   


    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<ResumeCommand>(this)
    );
    m_buttons[RESUME].setText("Resume", m_font, 24, sf::Color::White);


    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<PlayCommand>(m_controller)
    );
    m_buttons[PLAY_AGAIN].setText("Play Again", m_font, 24, sf::Color::White);



    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing*2),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<HelpCommand>(m_controller)
    );
    m_buttons[HELP].setText("Help", m_font, 24, sf::Color::White);


    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing * 3),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100), 2.f,
        std::make_unique<MusicToggleCommand>(nullptr)
    );
    updateMusicButtonText();


    m_buttons.emplace_back(
        sf::Vector2f(centerX, startY + spacing * 4),
        buttonWidth, buttonHeight,
        sf::Color(150, 50, 50), 2.f,        
        std::make_unique<ExitCommand>(m_controller)
    );
    m_buttons[EXIT].setText("Exit Game", m_font, 24, sf::Color::White);
}

void PauseScreen::updateMusicButtonText() {
    bool musicOn = MusicManager::getInstance().isMusicOn();
    std::string musicText = musicOn ? "Music: ON" : "Music: OFF";
    m_buttons[MUSIC_TOGGLE].setText(musicText, m_font, 24, sf::Color::White);
}

void PauseScreen::update(float deltaTime) {

}

void PauseScreen::draw() {

    if (m_gamePlay) {
        m_gamePlay->BaseScreen::draw();
    }


    m_window->draw(m_overlay);


    m_window->draw(m_pauseTitle);


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