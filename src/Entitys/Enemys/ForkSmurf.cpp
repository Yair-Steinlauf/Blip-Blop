#include "Enemys/ForkSmurf.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "DataLoader.h"

static bool regSmurf = EnemyFactory::instance().registerType(
	ObjectType::ForkSMURF,
	[](sfPos pos, b2World* world, Player* player) -> std::unique_ptr<BaseEntity> {
		return std::make_unique<ForkSmurf>(pos, world, player);
	}
);

ForkSmurf::ForkSmurf(sfPos pos, b2World* world, Player* player)
	: BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world, player, AnimationSet::ForkEnemy)

{
	m_moveComponent.setHealth(1);
	m_moveComponent.setSpeed(35);
}
