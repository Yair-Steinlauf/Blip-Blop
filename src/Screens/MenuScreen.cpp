#include "MenuScreen.h"
#include "ScreensFactory.h"
#include "DataLoader.h"
#include "Constance.h"

#include "Controller.h"
#include <iostream>
#include "MusicCommand.h"  
#include "MusicManager.h"
#include <HelpCommand.h>
#include <PlayCommand.h>
#include <ExitCommand.h>

// ����� MenuScreen �������
static auto registerMenuScreen = ScreenFactory::instance().registerType(
    ObjectType::MenuScreen,
    [](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen> {
        return std::make_unique<MenuScreen>(window);
    }
);


MenuScreen::MenuScreen(sf::RenderWindow* window, Controller* controller)
    : BaseScreen(window), m_controller(controller) {

    // ����� ���
    m_background.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MenuBackground));

    // ����� ����
    const int textSize = 35;
    sf::Font& font = DataLoader::getP2Font();

    // ����� ������� ����� ����
    float centerX = SCREEN_WIDTH / 2.0f;
    float startY = SCREEN_HEIGHT / 3.0f;
    float buttonSpacing = 80.0f;
    float buttonWidth = 200.0f;
    float buttonHeight = 60.0f;

    // ����� Play
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY),
        buttonWidth, buttonHeight,
        sf::Color::Green,
        3.0f,
        std::make_unique<PlayCommand>(m_controller)
    );
    m_buttons.back().setText("PLAY", font, textSize, sf::Color::Black);

    // ����� Help
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY + buttonSpacing),
        buttonWidth, buttonHeight,
        sf::Color::Blue,
        3.0f,
        std::make_unique<HelpCommand>(m_controller)  
    );
    m_buttons.back().setText("HELP", font, textSize, sf::Color::Black);

    // ����� Music (���!)
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY + 2 * buttonSpacing),
        buttonWidth, buttonHeight,
        sf::Color(150, 100, 0, 255), // ����
        3.0f,
        std::make_unique<MusicToggleCommand>(this)
    );
    m_buttons.back().setOutlineColor(sf::Color::Black);

    // ����� Exit
    m_buttons.emplace_back(
        sf::Vector2f(centerX - buttonWidth / 2, startY + 3 * buttonSpacing),
        buttonWidth, buttonHeight,
        sf::Color::Red,
        3.0f,
        std::make_unique<ExitCommand>(this)
    );
    m_buttons.back().setText("EXIT", font, textSize, sf::Color::Black);
    
    // ���� ���� ����� �������
    updateMusicButtonText();

    // ���� ������ ���
    MusicManager::getInstance().startBackgroundMusic();
}
void MenuScreen::updateMusicButtonText() {
    if (m_buttons.size() >= 3) {
        std::string musicText = MusicManager::getInstance().isMusicOn() ? "MUSIC: ON" : "MUSIC: OFF";
        m_buttons[2].setText(musicText, DataLoader::getP2Font(), 24, sf::Color::White);  // ����� ������� ��� ������
    }
}

void MenuScreen::toggleMusic() {
    MusicManager::getInstance().toggleMusic();
    updateMusicButtonText();
}

void MenuScreen::update(float deltaTime) {
    // ����� ������� �� �� ����
    for (auto& button : m_buttons) {
        // ��� ���� ������ �������� �� ������ �����
    }
}

void MenuScreen::draw() {
    BaseScreen::draw();  // ����� �� ����

    // ���� �������
    for (const auto& button : m_buttons) {
        button.draw(*m_window);
    }

    // ���� ����� �����
    sf::Font& font = DataLoader::getP2Font();
    sf::Text title;
    title.setFont(font);
    title.setString("GAME MENU");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Yellow);

    // ����� ������ ����� ������
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(SCREEN_WIDTH / 2.0f, 100.0f);

    m_window->draw(title);
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
                // ����� ���� ����� ����
                for (auto& button : m_buttons) {
                    if (button.isClicked(mouseX, mouseY)) {
                        button.trigger();  // ����� ������ �� ������
                        break;
                    }
                }
            }
        }
    }

    // ����� highlight �� �������
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