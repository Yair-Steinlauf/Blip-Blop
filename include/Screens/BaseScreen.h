#pragma once

#include "SFML/Graphics.hpp"

class BaseScreen {
public:
	BaseScreen() = default;
	virtual ~BaseScreen() = default;
	virtual void run() = 0;
protected:
	sf::RenderWindow& m_window;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void handleEvents() = 0;

};