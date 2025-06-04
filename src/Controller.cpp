#include "Controller.h"

Controller::Controller()
	: m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game Window"))
{
	m_screenStack.push(std::make_unique<GamePlay>());
}

void Controller::run()
{
}
