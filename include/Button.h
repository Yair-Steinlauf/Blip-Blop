#pragma once

#include <SFML/Graphics.hpp>
#include "Command.h"

class Button {
private:
    bool m_visible;       // Determines if the button is visible or hidden
    sf::Vector2f m_loc;   // Button position
    sf::Texture m_texture;
    sf::Sprite m_sprite;  // Sprite for button texture (if used)
    sf::RectangleShape m_background; // Background color if no texture is used
    sf::Text m_text;      // Text displayed on the button
    float m_borderThickness; // Border thickness
    int m_icon = 0;       // Integer representing the icon
    bool m_isHighlighted = false; // Determines if the button is highlighted
    bool m_useTexture = false;    // Determines if a texture is used
    std::unique_ptr<Command> m_command;

public:
    // Default constructor
    Button() = default;

    // Constructor with texture
    Button(const sf::Vector2f& position, const sf::Texture& texture, float width, float height, float borderThickness = 2.f, std::unique_ptr<Command> cmd = nullptr);

    // Constructor with background color
    Button(const sf::Vector2f& position, float width, float height, sf::Color backgroundColor, float borderThickness = 2.f, std::unique_ptr<Command> cmd = nullptr);

    // Check if the button is clicked
    bool isClicked(float mouseX, float mouseY) const;

    // Set highlight state
    void setHighlight(bool highlight);

    // Draw the button
    void draw(sf::RenderWindow& window) const;

    // Set button position
    void setPosition(const sf::Vector2f& position);

    // Get button position
    sf::Vector2f getPosition() const;

    // Set button size
    void setSize(float width, float height);

    // Get button size
    sf::Vector2f getSize() const;

  
    // Set button texture
    void setTexture(const sf::Texture& texture);

    // Set button background color (if no texture is used)
    void setBackgroundColor(sf::Color color);

    // Set border color
    void setOutlineColor(sf::Color color);

    // Get the sprite
    sf::Sprite& getSprite();

    // Set the icon value
    void setIcon(int icon);

    // Get the icon value
    int getIcon() const;

    // Set button visibility
    void setVisible(bool visible);

    // Check if the button is visible
    bool isVisible() const;

    // Set button text
    void setText(const std::string& text, const sf::Font& font, unsigned int size, sf::Color color = sf::Color::White);

    // Get the button text
    std::string getText() const;

    // Set text color
    void setTextColor(sf::Color color);
    /////////////////////////////////////////////////
    void setCommand(std::unique_ptr<Command> cmd);
    Command* getCommand() const;
    void trigger();
};


;