#pragma once

#include <SFML/Graphics.hpp>
#include "Command.h"

class Button {
private:
    float m_x, m_y;
    float m_width, m_height;
    const sf::Texture* m_texture;
    float m_borderThickness;
    char m_icon = ' ';
    bool m_isHighlighted = false;
    std::unique_ptr<Command> m_command; 
public:
    Button() = default;
    Button(float x, float y, float width, float height,
        const sf::Texture* texture,
        float borderThickness = 2.f,
        std::unique_ptr<Command> cmd = nullptr);

    bool isClicked(float mouseX, float mouseY) const;
    void setHighlight(bool highlight);
    void draw(sf::RenderWindow& window) const;

    void setPosition(float x, float y);
    void setSize(float width, float height);
    void getSize(float& width, float& height) const;
    void setBorderThickness(float thickness);
    void setTexture(const sf::Texture* texture);
    const sf::Texture* getTexture() const;
    void getPosition(float& x, float& y) const;
    void setIcon(char icon);
    char getIcon() const;

    void setCommand(std::unique_ptr<Command> cmd);
    Command* getCommand() const;
    void trigger();
};
