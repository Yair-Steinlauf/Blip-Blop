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
	: BaseEntity(pos, world) , m_moveComponent(std::make_unique<MoveComponent>(*this, world))
{
	initSprite(DataLoader::getInstance().getP2Texture(ObjectType::PLAYER));
	initBox2d(pos);
}

void Player::update(float deltaTime)
{
	if (m_moveComponent)
		m_moveComponent->update(deltaTime);
}
