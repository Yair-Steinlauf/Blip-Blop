#include "Controller.h"
#include "Screens/GamePlay.h"
#include "Factory/Factory.h"
#include "ScreensFactory.h"
#include "Constance.h"

Controller::Controller():
	m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Window"))
	, m_screenStack()
{

	m_screenStack.push(ScreenFactory::instance().create(ObjectType::GamePlay, m_window.get()));

}

void Controller::run()
{
	sf::Clock clock;
	while (m_window->isOpen())
	{
		sf::Event event;
		float deltaTime = clock.restart().asSeconds();
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
		}
		m_screenStack.top()->handleInput(event, deltaTime);
		m_screenStack.top()->update(deltaTime);
		m_window->clear();
		m_screenStack.top()->draw();
		m_window->display();
	}
}
