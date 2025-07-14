#include "Controller.h"
#include "Screens/GamePlay.h"
#include "Screens/MenuScreen.h"
#include "Screens/HelpScreen.h"
#include "Factory/Factory.h"
#include "ScreensFactory.h"
#include "Constance.h"
#include "MusicManager.h"
#include <PauseScreen.h>
#include <BaseEnemy.h>

Controller::Controller() :
	m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Blip &"))
	, m_screenStack()
{
	GameAnimations::initializeFrames();


	auto menuScreen = std::make_unique<MenuScreen>(m_window.get(), this);
	m_screenStack.push(std::move(menuScreen));


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

void Controller::closeGame()
{
	m_window->close();
}












void Controller::switchToGamePlay() {
	BaseEnemy::resetAliveCount();
	while (!m_screenStack.empty()) {
		m_screenStack.pop(); 		
	}
	auto gamePlay = std::make_unique<GamePlay>(m_window.get());
	gamePlay->setController(this);

	m_screenStack.push(std::move(gamePlay));

}

void Controller::switchToHelp() {

	auto helpScreen = std::make_unique<HelpScreen>(m_window.get(), this);
	m_screenStack.push(std::move(helpScreen));
}

void Controller::backCommand() {

	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}	
}

void Controller::pauseGame() {

	GamePlay* currentGamePlay = getCurrentGamePlay();
	if (currentGamePlay) {
		auto pauseScreen = std::make_unique<PauseScreen>(m_window.get(), this, currentGamePlay);
		m_screenStack.push(std::move(pauseScreen));
	}
}

void Controller::resumeFromPause() {

	if (!m_screenStack.empty()) {
		m_screenStack.pop();
	}
}

void Controller::switchToGameOver(GameOverScreen::GameResult result, int score)
{

	/*while (!m_screenStack.empty()) {
		m_screenStack.pop();
	}*/
	BaseEnemy::resetAliveCount();
	auto gameOverScreen = std::make_unique<GameOverScreen>(m_window.get(), result, score, this);
	m_screenStack.push(std::move(gameOverScreen));
}

GamePlay* Controller::getCurrentGamePlay()
{

	if (!m_screenStack.empty()) {
		return dynamic_cast<GamePlay*>(m_screenStack.top().get());
	}
	return nullptr;

}



