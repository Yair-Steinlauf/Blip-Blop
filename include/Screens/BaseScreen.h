#pragma once

#include "SFML/Graphics.hpp"

class BaseScreen {
public:
	BaseScreen(sf::RenderWindow* window);
	virtual ~BaseScreen() = default;
	virtual void update(float deltaTime) = 0;
	virtual void draw();
	virtual void handleInput(const sf::Event& event ,float deltaTime) = 0;

protected:
	sf::RenderWindow* m_window;
	sf::Sprite m_background;



};