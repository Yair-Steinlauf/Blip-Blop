#include "Player.h"
#include "Factory.h"
#include "Movment/StandMovment.h"

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

	m_sprite.setPosition({ 50,50 });
	m_movement = std::make_unique<StandMovement>();
}

void Player::handleInput(const sf::Event& event, float deltaTime)
{
}






