#pragma once
#include "BaseScreen.h"
#include "Button.h"
#include <vector>
#include <memory>

class Controller;

class GameOverScreen : public BaseScreen {
public:
    enum class GameResult {
        Victory,
        Defeat
    };

    GameOverScreen(sf::RenderWindow* window, GameResult result, int score, Controller* controller);
    ~GameOverScreen() override = default;

    void update(float deltaTime) override;
    void draw() override;
    void handleInput(const sf::Event& event, float deltaTime) override;

    void playAgain();
    void exitGame();
    void showHelp();
    void toggleMusic();

private:
    void initializeButtons();
    void setupResultDisplay();
    void updateMusicButtonText();

    GameResult m_result;
    int m_score;
    Controller* m_controller;

    // UI Elements
    sf::Sprite m_resultLogo;
    sf::Texture m_victoryTexture;
    sf::Texture m_defeatTexture;
    sf::Text m_scoreText;
    sf::Font m_font;

    // Buttons
    std::vector<Button> m_buttons;
    enum ButtonIndex {
        MUSIC_BUTTON = 0,
        PLAY_AGAIN_BUTTON = 1,
        EXIT_BUTTON = 2,
        HELP_BUTTON = 3
    };

    // Button hover tracking
    int m_hoveredButton = -1;

    // Commands
    std::unique_ptr<Command> m_playAgainCommand;
    std::unique_ptr<Command> m_exitCommand;
    std::unique_ptr<Command> m_helpCommand;
    std::unique_ptr<Command> m_musicCommand;
};