#pragma once

#include <SFML/Graphics.hpp>
#include "Command.h"

class Button {
private:
    bool m_visible;
    sf::Vector2f m_loc;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::RectangleShape m_background;
    sf::Text m_text;
    float m_borderThickness;
    int m_icon = 0;
    bool m_isHighlighted = false;
    bool m_useTexture = false;
    std::unique_ptr<Command> m_command;

public:

    Button() = default;


    Button(const sf::Vector2f& position, const sf::Texture& texture, float width, float height, float borderThickness = 2.f, std::unique_ptr<Command> cmd = nullptr);


    Button(const sf::Vector2f& position, float width, float height, sf::Color backgroundColor, float borderThickness = 2.f, std::unique_ptr<Command> cmd = nullptr);


    bool isClicked(float mouseX, float mouseY) const;


    void setHighlight(bool highlight);


    void draw(sf::RenderWindow& window) const;


    void setPosition(const sf::Vector2f& position);


    sf::Vector2f getPosition() const;


    void setSize(float width, float height);


    sf::Vector2f getSize() const;

  

    void setTexture(const sf::Texture& texture);


    void setBackgroundColor(sf::Color color);


    void setOutlineColor(sf::Color color);


    sf::Sprite& getSprite();


    void setIcon(int icon);


    int getIcon() const;


    void setVisible(bool visible);


    bool isVisible() const;


    void setText(const std::string& text, const sf::Font& font, unsigned int size, sf::Color color = sf::Color::White);


    std::string getText() const;


    void setTextColor(sf::Color color);

    void setCommand(std::unique_ptr<Command> cmd);
    Command* getCommand() const;
    void trigger();
};


;