#include "GamePlay.h"
#include "ScreensFactory.h"
#include "Player.h"

static auto registerIt = ScreenFactory::instance().registerType(
	ObjectType::GamePlay,
	[](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen>
	{
		return std::make_unique<GamePlay>(window);
	}
);

GamePlay::GamePlay(sf::RenderWindow* window):
	BaseScreen(window),m_window(window),
	m_world(std::make_unique<b2World>(b2Vec2(0.f, 9.81f))),
	m_player(std::make_unique<Player>(sfPos{ 500, 50 }, m_world.get())),
	m_level(m_player.get(), m_world.get())
{
}

void GamePlay::update(float deltaTime)
{
	m_world->Step(deltaTime, 8, 3); // 8 velocity iterations, 3 position iterations
	m_level.update(deltaTime);
	for (auto& c : m_cubes)
		c.update();
}

void GamePlay::draw()
{
	BaseScreen::draw();
	m_level.draw(*m_window);
	for (const auto& c : m_cubes)
		m_window->draw(c.shape);
}

void GamePlay::handleInput(const sf::Event& event, float deltaTime)
{
	            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
				
				m_cubes.push_back(Cube(*m_world.get(), mousePos.x, mousePos.y));
            }
	//TODO:: maybe not needed parameters (const sf::Event& event, float deltaTime)
	m_player->movment();
}
