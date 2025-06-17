#include "Player.h"
#include "Factory.h"
#include "Movment/PlayerStandMovment.h"

static auto registerIt = Factory::instance().registerType(
	ObjectType::PLAYER,
	[](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
	{
		return std::make_unique<Player>(pos, world);
	}
);


Player::Player(sfPos pos, b2World* world)
	:AttackingEntity(pos, world)
{
	m_movement = std::make_unique<PlayerStandMovement>(*this);
	initSprite(DataLoader::getInstance().getP2Texture(ObjectType::PLAYER));
	initBox2d(pos);

}
