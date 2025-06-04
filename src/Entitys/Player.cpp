#include "Player.h"
#include "PlayerRegularMove.h"
static auto registerIt = Factory<MovingEntity>::instance().registerType(
	ObjectType::PLAYER,
	[]() -> std::unique_ptr<MovingEntity>
	{
		return std::make_unique<Player>();
	}
);

Player::Player()
{
	m_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::PLAYER));
	m_movement = std::make_unique<PlayerRegularMove>(300.f);
	m_sprite.setPosition({ 50,50 });
}

void Player::handleInput(const sf::Event& event, float deltaTime)
{
	m_nextPosition = m_movement->move(*this, deltaTime);
}
