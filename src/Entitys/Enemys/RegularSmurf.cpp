#include "RegularSmurf.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "DataLoader.h"

static bool regRegularSmurf = EnemyFactory::instance().registerType(
	ObjectType::RegularSmurf,
	[](sfPos pos, b2World* world, Player* player) -> std::unique_ptr<BaseEntity> {
		return std::make_unique<RegularSmurf>(pos, world, player);
	}
);

RegularSmurf::RegularSmurf(sfPos pos, b2World* world, Player* player)
	: BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world, player, AnimationSet::StandardEnemy)

{
}

