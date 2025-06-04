#include "Player.h"
#include "PlayerRegularMove.h"
static auto registerIt = Factory<MovingEntity>::instance().registerType(
	ObjectType::Player,
	[]() -> std::unique_ptr<MovingEntity>
	{
		return std::make_unique<Player>();
	}
);

Player::Player()
{
	m_movement = std::make_unique<PlayerRegularMove>(300.f);
	sf::Image im;
	im.create(15, 15, sf::Color::Green);
	sf::Texture txtue;
	txtue.loadFromImage(im);
	m_sprite.setTexture(txtue);
	m_sprite.setPosition({ 50,50 });
}

void Player::handleInput(const sf::Event& event, float deltaTime)
{
	m_nextPosition = m_movement->move(*this, deltaTime);
}
