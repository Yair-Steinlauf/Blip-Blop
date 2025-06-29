#include "GamePlay.h"
#include "ScreensFactory.h"
#include "Player.h"

static auto registerGamePlay = ScreenFactory::instance().registerType(
    ObjectType::GamePlay,
    [](sf::RenderWindow* window) -> std::unique_ptr<BaseScreen> {
        return std::make_unique<GamePlay>(window);
    }
);

GamePlay::GamePlay(sf::RenderWindow* window):
	BaseScreen(window),m_window(window),
	m_world(std::make_unique<b2World>(b2Vec2(0.f, 9.81f))),
	m_player(std::make_unique<Player>(sfPos{ 0, 50 }, m_world.get())),
	m_level(m_player.get(), m_world.get())
{
	m_player->setGamePlay(this);

	// יצירת מאזין התנגשויות והגדרתו לעולם
	m_contactListener = std::make_unique<ContactListener>();
	m_world->SetContactListener(m_contactListener.get());
}

void GamePlay::update(float deltaTime)
{
	centerCameraOnPlayer();

	m_world->Step(deltaTime, 8, 3); // 8 velocity iterations, 3 position iterations
	m_level.update(deltaTime);

	//לעקוב אחרי מיקום השחקן

	for (auto& c : m_cubes)
		c.update();
}

void GamePlay::draw()
{
	BaseScreen::draw();
	centerCameraOnPlayer();   // ממרכז את המצלמה
	m_level.draw(*m_window);

	drawUI();
}

void GamePlay::handleInput(const sf::Event& event, float deltaTime)
{

	//TODO:: maybe not needed parameters (const sf::Event& event, float deltaTime)
	//m_player->movment();
}

sf::Vector2f GamePlay::getMouseWorldPosition()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*m_window); // window = sf::RenderWindow שלך
	sf::Vector2f worldPos = m_window->mapPixelToCoords(pixelPos);
	return worldPos;
}

void GamePlay::addEntity(std::unique_ptr<BaseEntity> entity) {
	m_level.addEntity(std::move(entity));
}

void GamePlay::drawUI()
{
	m_window->setView(m_window->getDefaultView());

	m_player->drawLifeBar(*m_window);
}

void GamePlay::centerCameraOnPlayer() {
	sf::View view = m_window->getView();
	sf::Vector2f playerPos = m_player->getPosition();
	sf::Vector2f viewSize = view.getSize();
	float halfViewWidth = viewSize.x / 2.f;

	const sf::Sprite& background = m_level.getBackground();
	float backgroundWidth = background.getGlobalBounds().width;

	float minX = halfViewWidth;
	float maxX = backgroundWidth - halfViewWidth;
	float cameraX = std::clamp(playerPos.x, minX, maxX);

	view.setCenter(cameraX, view.getCenter().y);
	m_window->setView(view);
}
