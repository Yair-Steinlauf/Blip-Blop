#include "Button.h"
#include <stdexcept>
#include <iostream>


Button::Button(const sf::Vector2f& position, const sf::Texture& texture, float width, float height, float borderThickness, std::unique_ptr<Command> cmd)
    : m_loc(position), m_borderThickness(borderThickness), m_visible(true), m_useTexture(true), m_command(std::move(cmd)) {


    m_background.setSize(sf::Vector2f(width, height));
    m_background.setPosition(position);
    m_texture = texture;
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_loc);
    m_sprite.setScale(
        width / m_texture.getSize().x,
        height / m_texture.getSize().y
    );
}


Button::Button(const sf::Vector2f& position, float width, float height, sf::Color backgroundColor, float borderThickness, std::unique_ptr<Command> cmd)
    : m_loc(position), m_borderThickness(borderThickness), m_visible(true), m_useTexture(false), m_command(std::move(cmd)) {

    m_background.setSize(sf::Vector2f(width, height));
    m_background.setPosition(position);
    m_background.setFillColor(backgroundColor);
    m_background.setOutlineThickness(borderThickness);
    m_background.setOutlineColor(sf::Color::Black);
}


bool Button::isClicked(float mouseX, float mouseY) const {

    if (!m_visible) return false;
    return (m_background.getGlobalBounds().contains(mouseX, mouseY));
}


void Button::setHighlight(bool highlight) {
    m_isHighlighted = highlight;
}


void Button::draw(sf::RenderWindow& window) const {
    if (!m_visible) return;

    if (m_useTexture) {
        window.draw(m_sprite);
    }
    else {
        window.draw(m_background);
    }


    if (m_isHighlighted) {
        sf::RectangleShape overlay(m_background.getSize());
        overlay.setPosition(m_loc);
        overlay.setFillColor(sf::Color(0, 0, 0, 80));

        window.draw(overlay);
    }


    window.draw(m_text);
}


void Button::setPosition(const sf::Vector2f& position) {
    m_loc = position;
    if (m_useTexture) {
        m_sprite.setPosition(position);
    }
    else {
        m_background.setPosition(position);
    }
    m_text.setPosition(position.x + m_background.getSize().x / 4, position.y + m_background.getSize().y / 4);
}


sf::Vector2f Button::getPosition() const {
    return m_loc;
}


void Button::setSize(float width, float height) {
    if (m_useTexture) {
        m_sprite.setScale(
            width / m_sprite.getTexture()->getSize().x,
            height / m_sprite.getTexture()->getSize().y
        );
    }
    else {
        m_background.setSize(sf::Vector2f(width, height));
    }
}


sf::Vector2f Button::getSize() const {
    return m_useTexture ? sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height) : m_background.getSize();
}


void Button::setBackgroundColor(sf::Color color) {
    if (!m_useTexture) {
        m_background.setFillColor(color);
    }
}


void Button::setOutlineColor(sf::Color color) {
    if (!m_useTexture) {
        m_background.setOutlineColor(color);
    }
}


void Button::setTexture(const sf::Texture& texture) {
    m_texture = texture;
    m_sprite.setTexture(m_texture);


    m_sprite.setScale(
        m_background.getSize().x / m_texture.getSize().x,
        m_background.getSize().y / m_texture.getSize().y
    );
}


sf::Sprite& Button::getSprite() {
    return m_sprite;
}


void Button::setIcon(int icon) {
    m_icon = icon;
}


int Button::getIcon() const {
    return m_icon;
}


void Button::setVisible(bool visible) {
    m_visible = visible;
}


bool Button::isVisible() const {
    return m_visible;
}


void Button::setText(const std::string& text, const sf::Font& font, unsigned int size, sf::Color color) {
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(size);
    m_text.setFillColor(color);

    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    m_text.setPosition(m_loc.x + m_background.getSize().x / 2, m_loc.y + m_background.getSize().y / 2 - textBounds.height / 4);
}


std::string Button::getText() const {
    return m_text.getString();
}


void Button::setTextColor(sf::Color color) {
    m_text.setFillColor(color);
}

void Button::setCommand(std::unique_ptr<Command> cmd) {
    m_command = std::move(cmd);
}

Command* Button::getCommand() const {
    return m_command.get();
}

void Button::trigger() {
    if (m_command)
        m_command->execute();
}