#include "Enemys/Smurf.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "DataLoader.h"

static bool regSmurf = EnemyFactory::instance().registerType(
	ObjectType::SMURF,
	[](sfPos pos, b2World* world, Player* player) -> std::unique_ptr<BaseEntity> {
		return std::make_unique<Smurf>(pos, world, player);
	}
);

Smurf::Smurf(sfPos pos, b2World* world, Player* player)
	: BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::SMURF), pos, world, player)
{
}
