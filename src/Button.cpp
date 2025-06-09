#include "Button.h"
#include <stdexcept>

// Constructor
Button::Button(float x, float y, float width, float height,
    const sf::Texture* texture,
    float borderThickness,
    std::unique_ptr<Command> cmd)
    : m_x(x), m_y(y), m_width(width), m_height(height),
    m_texture(texture), m_borderThickness(borderThickness),
    m_command(std::move(cmd)) {
}


// Check if the button is clicked
bool Button::isClicked(float mouseX, float mouseY) const {
    float innerLeft = m_x + m_borderThickness;
    float innerTop = m_y + m_borderThickness;
    float innerRight = innerLeft + m_width - 2 * m_borderThickness;
    float innerBottom = innerTop + m_height - 2 * m_borderThickness;

    return mouseX >= innerLeft && mouseX <= innerRight &&
        mouseY >= innerTop && mouseY <= innerBottom;
}

// Set highlight state
void Button::setHighlight(bool highlight) {
    m_isHighlighted = highlight;
}

// Draw the button
void Button::draw(sf::RenderWindow& window) const {
    if (!m_texture) {
        throw std::runtime_error("Button texture is null!");
    }

    // Draw the border
    sf::RectangleShape borderShape(sf::Vector2f(m_width, m_height));
    borderShape.setPosition(m_x, m_y);
    borderShape.setFillColor(sf::Color::Transparent); // Transparent background
    borderShape.setOutlineThickness(m_borderThickness);

    // Calculate the inner bounds of the texture
    float innerWidth = m_width - 2 * m_borderThickness;
    float innerHeight = m_height - 2 * m_borderThickness;
    float innerX = m_x + m_borderThickness;
    float innerY = m_y + m_borderThickness;

    // Draw the texture inside the button
    sf::Sprite sprite(*m_texture);
    sprite.setScale(
        innerWidth / m_texture->getSize().x,  // Scale width
        innerHeight / m_texture->getSize().y // Scale height
    );
    sprite.setPosition(innerX, innerY);

    // Render the border and the texture
    window.draw(borderShape);
    window.draw(sprite);

    // If the button is highlighted, draw a semi-transparent red overlay
    if (m_isHighlighted) {
        sf::RectangleShape overlay(sf::Vector2f(innerWidth, innerHeight));
        overlay.setPosition(innerX, innerY);
        overlay.setFillColor(sf::Color(255, 0, 0, 128)); // Semi-transparent red
        window.draw(overlay);
    }
}

// Set button position
void Button::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

// Get button position
void Button::getPosition(float& x, float& y) const {
    x = m_x;
    y = m_y;
}

// Set button size
void Button::setSize(float width, float height) {
    m_width = width;
    m_height = height;
}

// Get button size
void Button::getSize(float& width, float& height) const {
    width = m_width;
    height = m_height;
}

// Set border thickness
void Button::setBorderThickness(float thickness) {
    m_borderThickness = thickness;
}

// Set button texture
void Button::setTexture(const sf::Texture* texture) {
    if (!texture) {
        throw std::runtime_error("Texture pointer is null!");
    }
    m_texture = texture;
}

// Get the pointer to the button texture
const sf::Texture* Button::getTexture() const {
    return m_texture;
}


// Set the icon character
void Button::setIcon(char icon) {
    m_icon = icon;
}

// Get the icon character
char Button::getIcon() const {
    return m_icon;
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
