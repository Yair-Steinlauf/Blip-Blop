#include "Controller.h"
#include "Screens/GamePlay.h"
#include "Screens/MenuScreen.h"
#include "Factory/Factory.h"
#include "ScreensFactory.h"
#include "Constance.h"

Controller::Controller() :
	m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Window"))
	, m_screenStack()
{
	GameAnimations::initializeFrames();
	// התחל עם MenuScreen ותעביר את ה-Controller
	auto menuScreen = std::make_unique<MenuScreen>(m_window.get(), this);
	m_screenStack.push(std::move(menuScreen));
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

		if (!m_screenStack.empty()) {
			m_screenStack.top()->handleInput(event, deltaTime);
			m_screenStack.top()->update(deltaTime);
			m_window->clear();
			m_screenStack.top()->draw();
			m_window->display();
		}
	}
}

void Controller::switchToGamePlay() {
	// מחק את המסך הנוכחי (MenuScreen)
	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}

	// הוסף את מסך המשחק
	auto gamePlayScreen = std::make_unique<GamePlay>(m_window.get());
	m_screenStack.push(std::move(gamePlayScreen));
}