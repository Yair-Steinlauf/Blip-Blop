#include "Controller.h"
#include "Screens/GamePlay.h"
#include "Screens/MenuScreen.h"
#include "Screens/HelpScreen.h"
#include "Factory/Factory.h"
#include "ScreensFactory.h"
#include "Constance.h"
#include "MusicManager.h"  // <-- ���� �� ��

Controller::Controller() :
	m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Window"))
	, m_screenStack()
{
	GameAnimations::initializeFrames();

	// ���� �� MenuScreen ������ �� �-Controller
	auto menuScreen = std::make_unique<MenuScreen>(m_window.get(), this);
	m_screenStack.push(std::move(menuScreen));

	// ���� ������ ��� (�� ��� �� ������ ���)
	MusicManager::getInstance().startBackgroundMusic();
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
			if (event.type == sf::Event::Closed) {
				// ���� ������ ���� �����
				MusicManager::getInstance().stopBackgroundMusic();
				m_window->close();
			}
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
	// ��� �� ���� ������
	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}

	// ���� �� ��� �����
	auto gamePlayScreen = std::make_unique<GamePlay>(m_window.get());
	m_screenStack.push(std::move(gamePlayScreen));
}

void Controller::switchToHelp() {
	// ��� �� ���� ������ (MenuScreen)
	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}

	// ���� �� ��� �����
	auto helpScreen = std::make_unique<HelpScreen>(m_window.get(), this);
	m_screenStack.push(std::move(helpScreen));
}

void Controller::backCommand() {
	// ��� �� ���� ������ (HelpScreen �� GamePlay)
	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}

	// ���� �� ��� ������
	auto menuScreen = std::make_unique<MenuScreen>(m_window.get(), this);
	m_screenStack.push(std::move(menuScreen));
}