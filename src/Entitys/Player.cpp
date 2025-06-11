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


Player::Player(sfPos pos, b2World* world)
	:AttackingEntity(pos, world)
{
	m_movement = std::make_unique<StandMovement>();
	initSprite(DataLoader::getInstance().getP2Texture(ObjectType::PLAYER));
	initBox2d(pos);

}
