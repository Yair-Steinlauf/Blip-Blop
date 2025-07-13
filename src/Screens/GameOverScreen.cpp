#include "GameOverScreen.h"
#include "DataLoader.h"
#include "PlayCommand.h"
#include "ExitCommand.h"
#include "HelpCommand.h"
#include "MusicCommand.h"
#include "MusicManager.h"
#include "Controller.h"
#include <iostream>

GameOverScreen::GameOverScreen(sf::RenderWindow* window, GameResult result, int score, Controller* controller)
    : BaseScreen(window), m_result(result), m_score(score), m_controller(controller), m_hoveredButton(-1)
{
    // Load font
    m_font = DataLoader::getInstance().getP2Font();

    // Load result textures
    if (!m_victoryTexture.loadFromFile("victory.png")) {
        std::cerr << "Failed to load victory.png" << std::endl;
    }
    if (!m_defeatTexture.loadFromFile("defeat.png")) {
        std::cerr << "Failed to load defeat.png" << std::endl;
    }

    // Setup background
    //m_background.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MenuBackground));
    //sf::Vector2u windowSize = window->getSize();
    //sf::Vector2u textureSize = m_background.getTexture()->getSize();
    /*m_background.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );*/

    setupResultDisplay();
    initializeButtons();
}

void GameOverScreen::setupResultDisplay() {
    sf::Vector2u windowSize = m_window->getSize();

    // Setup result logo
    if (m_result == GameResult::Victory) {
        m_resultLogo.setTexture(m_victoryTexture);
    }
    else {
        m_resultLogo.setTexture(m_defeatTexture);
    }

    // Center the logo
    sf::FloatRect logoBounds = m_resultLogo.getLocalBounds();
    m_resultLogo.setOrigin(logoBounds.width / 2.f, logoBounds.height / 2.f);
    m_resultLogo.setPosition(windowSize.x / 2.f, windowSize.y / 3.f);

    // Setup score text only (no title text)
    m_scoreText.setFont(m_font);
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(36);
    m_scoreText.setFillColor(sf::Color::White);
    sf::FloatRect scoreBounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreBounds.width / 2.f, scoreBounds.height / 2.f);
    m_scoreText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void GameOverScreen::initializeButtons() {
    sf::Vector2u windowSize = m_window->getSize();
    float buttonWidth = 180.f;
    float buttonHeight = 60.f;
    float horizontalSpacing = 300.f; // מרחק בין העמודות
    float verticalSpacing = 80.f;    // מרחק בין הכפתורים בעמודה

    // חישוב מיקומים - שתי עמודות
    float leftColumnX = windowSize.x / 2.f - horizontalSpacing / 2.f - buttonWidth / 2.f;
    float rightColumnX = windowSize.x / 2.f + horizontalSpacing / 2.f - buttonWidth / 2.f;
    float startY = windowSize.y / 2.f + 80.f; // מתחת לניקוד

    // Create commands
    m_playAgainCommand = std::make_unique<PlayCommand>(m_controller);
    m_exitCommand = std::make_unique<ExitCommand>(m_controller);
    m_helpCommand = std::make_unique<HelpCommand>(m_controller);
    m_musicCommand = std::make_unique<MusicToggleCommand>(nullptr);

    m_buttons.clear();
    m_buttons.resize(4);

    // Left column - top button (Music)
    m_buttons[MUSIC_BUTTON] = Button(
        sf::Vector2f(leftColumnX, startY),
        buttonWidth, buttonHeight,
        sf::Color(70, 70, 70),
        2.f
    );
    updateMusicButtonText();

    // Left column - bottom button (Help)
    m_buttons[HELP_BUTTON] = Button(
        sf::Vector2f(leftColumnX, startY + verticalSpacing),
        buttonWidth, buttonHeight,
        sf::Color(0, 0, 150),
        2.f
    );
    m_buttons[HELP_BUTTON].setText("HELP", m_font, 24, sf::Color::White);

    // Right column - top button (Play Again)
    m_buttons[PLAY_AGAIN_BUTTON] = Button(
        sf::Vector2f(rightColumnX, startY),
        buttonWidth, buttonHeight,
        sf::Color(0, 150, 0),
        2.f
    );
    m_buttons[PLAY_AGAIN_BUTTON].setText("PLAY AGAIN", m_font, 20, sf::Color::White);

    // Right column - bottom button (Exit)
    m_buttons[EXIT_BUTTON] = Button(
        sf::Vector2f(rightColumnX, startY + verticalSpacing),
        buttonWidth, buttonHeight,
        sf::Color(150, 0, 0),
        2.f
    );
    m_buttons[EXIT_BUTTON].setText("EXIT", m_font, 24, sf::Color::White);
}

void GameOverScreen::updateMusicButtonText() {
    bool musicOn = MusicManager::getInstance().isMusicOn();
    m_buttons[MUSIC_BUTTON].setText(
        musicOn ? "MUSIC: ON" : "MUSIC: OFF",
        m_font, 24, sf::Color::White
    );
}

void GameOverScreen::update(float deltaTime) {
    // Update button hover states
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
    int newHoveredButton = -1;

    for (size_t i = 0; i < m_buttons.size(); ++i) {
        if (m_buttons[i].isClicked(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            newHoveredButton = static_cast<int>(i);
            break;
        }
    }

    // Update highlight states
    if (newHoveredButton != m_hoveredButton) {
        if (m_hoveredButton >= 0) {
            m_buttons[m_hoveredButton].setHighlight(false);
        }
        if (newHoveredButton >= 0) {
            m_buttons[newHoveredButton].setHighlight(true);
        }
        m_hoveredButton = newHoveredButton;
    }
}

void GameOverScreen::draw() {
    BaseScreen::draw(); // Draw background

    // Draw result logo
    m_window->draw(m_resultLogo);

    // Draw score text only (no title text)
    m_window->draw(m_scoreText);

    // Draw buttons
    for (const auto& button : m_buttons) {
        button.draw(*m_window);
    }
}

void GameOverScreen::handleInput(const sf::Event& event, float deltaTime) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        m_mousePressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y));
            if (m_mousePressed)
            {
                m_mousePressed = false;
                if (m_buttons[MUSIC_BUTTON].isClicked(mousePos.x, mousePos.y)) {
                    toggleMusic();
                }
                else if (m_buttons[PLAY_AGAIN_BUTTON].isClicked(mousePos.x, mousePos.y)) {
                    playAgain();
                }
                else if (m_buttons[EXIT_BUTTON].isClicked(mousePos.x, mousePos.y)) {
                    exitGame();
                }
                else if (m_buttons[HELP_BUTTON].isClicked(mousePos.x, mousePos.y)) {
                    showHelp();
                }
            }
        }
    }

    // Handle keyboard shortcuts
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::R:
            playAgain();
            break;
        case sf::Keyboard::Escape:
            exitGame();
            break;
        case sf::Keyboard::H:
            showHelp();
            break;
        case sf::Keyboard::M:
            toggleMusic();
            break;
        default:
            break;
        }
    }
}

void GameOverScreen::playAgain() {
    if (m_controller) {
        m_controller->switchToGamePlay();
    }
}

void GameOverScreen::exitGame() {
    if (m_window) {
        m_window->close();
    }
}

void GameOverScreen::showHelp() {
    if (m_controller) {
        m_controller->switchToHelp();
    }
}

void GameOverScreen::toggleMusic() {

    MusicManager::getInstance().toggleMusic();
    updateMusicButtonText();
}