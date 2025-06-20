#include "Player.h"
#include "Factory.h"
#include "DataLoader.h"

static auto registerIt = Factory::instance().registerType(
	ObjectType::PLAYER,
	[](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
	{
		return std::make_unique<Player>(pos, world);
	}
);

Player::Player(sfPos pos, b2World* world)
	: BaseEntity(&DataLoader::getInstance().getP2Texture(ObjectType::PLAYER),pos, world),
	m_moveComponent(*this)
{
}

void Player::update(float deltaTime)
{
	BaseEntity::update(deltaTime);

	m_moveComponent.update(deltaTime);
}
