#include "HelpScreen.h"
#include "ScreensFactory.h"
#include "DataLoader.h"
#include "Constance.h"
#include "Controller.h"

#include <iostream>
#include <BackCommand.h>

// ����� HelpScreen �������
static auto registerHelpScreen = ScreenFactory::instance().registerType(
    ObjectType::HelpScreen,
    [](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen> {
        return std::make_unique<HelpScreen>(window);
    }
);

HelpScreen::HelpScreen(sf::RenderWindow* window, Controller* controller)
    : BaseScreen(window), m_controller(controller) {

    // ����� ���
    m_background.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MenuBackground));


        try {
            sf::Font& dataFont = DataLoader::getP2Font();
            m_font = dataFont;
            m_fontLoaded = true;
            std::cout << "Help screen DataLoader font loaded successfully!" << std::endl;
        }
        catch (...) {
            std::cout << "Failed to load font for help screen" << std::endl;
        }
    

    // ����� ����� ���� ����� ������� �������
    float buttonWidth = 100.0f;
    float buttonHeight = 40.0f;
    float backButtonX = 20.0f;  // ����
    float backButtonY = 20.0f;  // �����

    m_buttons.emplace_back(
        sf::Vector2f(backButtonX, backButtonY),
        buttonWidth, buttonHeight,
        sf::Color(100, 100, 100, 255), // ����
        2.0f,
        std::make_unique<BackCommand>(m_controller)
    );
    m_buttons.back().setOutlineColor(sf::Color::White);

    if (m_fontLoaded) {
        m_buttons.back().setText("BACK", m_font, 20, sf::Color::White);
        std::cout << "Set BACK button text" << std::endl;
    }

    // ����� ���� �����
    initializeHelpText();
    updateScrollLimits();
}

void HelpScreen::initializeHelpText() {
    m_helpText = {
        "GAME CONTROLS:",
        "",
        "A / Left Arrow  -  Move Left",
        "D / Right Arrow  -  Move Right",
        "SPACE  -  Jump",
        "Mouse Movement  -  Aim weapon",
        "Left Mouse Click  -  Shoot",
        "",
        "GAME OBJECTIVES:",
        "",
        "� Collect gifts to upgrade your weapon",
        "� Green gift = Single shot weapon",
        "� Blue gift = Triple shot weapon",
        "� Red gift = Extra life",
        "� Defeat enemies by shooting them",
        "� Avoid taking damage",
        "",
        "GAMEPLAY TIPS:",
        "",
        "� Use platforms to jump higher",
        "� Aim carefully to hit enemies",
        "� Collect weapon upgrades strategically",
        "� Different weapons have different cooldowns",
        "� Triple shot is powerful but slower",
        "� Single shot is faster but less damage",
        "",
        "ENEMY TYPES:",
        "",
        "� Smurf - Basic enemy that follows you",
        "� Shoots bullets at your location",
        "� Avoid their projectiles",
        "",
        "MOVEMENT MECHANICS:",
        "",
        "� Physics-based movement system",
        "� Momentum affects your jumps",
        "� Use walls and platforms strategically",
        "� Landing softly preserves health",
        "",
        "WEAPON SYSTEM:",
        "",
        "� Mouse controls aiming direction",
        "� 8-directional shooting",
        "� Bullets have limited range",
        "� Different animations for each direction",
        "",
        "SCROLLING CONTROLS:",
        "",
        "� Mouse Wheel - Scroll up/down",
        "� Up/Down Arrow Keys - Scroll",
        "� Page Up/Page Down - Fast scroll",
        "",
        "Have fun playing!"
    };
}

void HelpScreen::updateScrollLimits() {
    if (!m_fontLoaded) return;

    float lineSpacing = 25.0f;
    float contentHeight = m_helpText.size() * lineSpacing;
    float visibleHeight = SCREEN_HEIGHT - 150.0f; // ����� ���� ����� ������

    m_maxScrollOffset = std::max(0.0f, contentHeight - visibleHeight);
}

void HelpScreen::update(float deltaTime) {
    // ����� ������ ����� �����
    m_scrollOffset = std::max(0.0f, std::min(m_scrollOffset, m_maxScrollOffset));
}

void HelpScreen::draw() {
    BaseScreen::draw();  // ����� �� ����

    if (!m_fontLoaded) return;

    // ���� ����� �����
    sf::Text title;
    title.setFont(m_font);
    title.setString("GAME HELP");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Yellow);

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(SCREEN_WIDTH / 2.0f, 80.0f);
    m_window->draw(title);

    // ����� ���� ������� ����� ������
    sf::View originalView = m_window->getView();
    sf::View scrollView = originalView;

    // ����� ���� ������ ������ (���� ������ ���� �������)
    float scrollAreaTop = 120.0f;
    float scrollAreaHeight = SCREEN_HEIGHT - 160.0f;

    scrollView.setViewport(sf::FloatRect(0, scrollAreaTop / SCREEN_HEIGHT, 1, scrollAreaHeight / SCREEN_HEIGHT));
    scrollView.setSize(SCREEN_WIDTH, scrollAreaHeight);
    scrollView.setCenter(SCREEN_WIDTH / 2, scrollAreaHeight / 2 + m_scrollOffset); // ��� ����� �����

    m_window->setView(scrollView);

    // ���� ���� ����� �� �����
    float startY = 30.0f; // ����� ����� ����� ������
    float lineSpacing = 25.0f;

    for (size_t i = 0; i < m_helpText.size(); ++i) {
        sf::Text line;
        line.setFont(m_font);
        line.setString(m_helpText[i]);

        // ������ ���� ������ ����� ����
        if (m_helpText[i].find(":") != std::string::npos && m_helpText[i] != "") {
            line.setCharacterSize(24);
            line.setFillColor(sf::Color::Cyan);
        }
        // ����� �� ������
        else if (m_helpText[i].find("�") != std::string::npos) {
            line.setCharacterSize(18);
            line.setFillColor(sf::Color::White);
        }
        // ���� ����
        else {
            line.setCharacterSize(20);
            line.setFillColor(sf::Color::White);
        }

        line.setPosition(50.0f, startY + i * lineSpacing);
        m_window->draw(line);
    }

    // ���� ������ �������
    m_window->setView(originalView);

    // ���� ����� ���� (��� ���)
    for (const auto& button : m_buttons) {
        button.draw(*m_window);
    }

    // ������ ����� ������
    sf::Text scrollInstructions;
    scrollInstructions.setFont(m_font);
    scrollInstructions.setString("Use Mouse Wheel or Arrow Keys to scroll");
    scrollInstructions.setCharacterSize(14);
    scrollInstructions.setFillColor(sf::Color(180, 180, 180));

    sf::FloatRect instrBounds = scrollInstructions.getLocalBounds();
    scrollInstructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
    scrollInstructions.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 20.0f);
    m_window->draw(scrollInstructions);

    // ��������� ����� (�� �� ��� ����)
    if (m_maxScrollOffset > 0) {
        // ���� �����
        float scrollBarHeight = 200.0f;
        float scrollBarWidth = 8.0f;
        float scrollBarX = SCREEN_WIDTH - 20.0f;
        float scrollBarY = 140.0f;

        // ��� ���� ������
        sf::RectangleShape scrollBarBg;
        scrollBarBg.setSize(sf::Vector2f(scrollBarWidth, scrollBarHeight));
        scrollBarBg.setPosition(scrollBarX, scrollBarY);
        scrollBarBg.setFillColor(sf::Color(100, 100, 100, 100));
        m_window->draw(scrollBarBg);

        // ���� ������
        float handleHeight = scrollBarHeight * (scrollAreaHeight / (scrollAreaHeight + m_maxScrollOffset)); 
        float handleY = scrollBarY + (m_scrollOffset / m_maxScrollOffset) * (scrollBarHeight - handleHeight);

        sf::RectangleShape scrollHandle;
        scrollHandle.setSize(sf::Vector2f(scrollBarWidth, handleHeight));
        scrollHandle.setPosition(scrollBarX, handleY);
        scrollHandle.setFillColor(sf::Color(200, 200, 200, 200));
        m_window->draw(scrollHandle);
    }
}

void HelpScreen::handleInput(const sf::Event& event, float deltaTime) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            float mouseX = static_cast<float>(event.mouseButton.x);
            float mouseY = static_cast<float>(event.mouseButton.y);

            // ����� ���� ����� ����
            for (auto& button : m_buttons) {
                if (button.isClicked(mouseX, mouseY)) {
                    std::cout << "Back button clicked!" << std::endl;
                    button.trigger();
                    break;
                }
            }
        }
    }

    // ����� �� ���� �����
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            m_scrollOffset -= event.mouseWheelScroll.delta * m_scrollSpeed; // ���� �� ������
        }
    }

    // ����� �� ���� �����
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            m_scrollOffset -= m_scrollSpeed; // ���� �� ������
            break;
        case sf::Keyboard::Down:
            m_scrollOffset += m_scrollSpeed; // ���� �� ������
            break;
        case sf::Keyboard::PageUp:
            m_scrollOffset += m_scrollSpeed * 5; // ���� �� ������ - ����� ����� �����
            break;
        case sf::Keyboard::PageDown:
            m_scrollOffset -= m_scrollSpeed * 5; // ���� �� ������ - ����� ����� ����
            break;
        case sf::Keyboard::Home:
            m_scrollOffset = m_maxScrollOffset; // ���� ������ ����� (�����)
            break;
        case sf::Keyboard::End:
            m_scrollOffset = 0; // ����� ���� ����� (����)
            break;
        case sf::Keyboard::Escape:
            backButton();
            break;
        default:
            break;
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

void HelpScreen::backButton() {
    if (m_controller) {
        m_controller->backCommand();
    }
}