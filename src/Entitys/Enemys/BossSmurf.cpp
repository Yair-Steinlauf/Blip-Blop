#include "BossSmurf.h"
#include "EnemyFactory.h"
#include "Player.h" 
#include "DataLoader.h"

//static bool regBossSmurf = EnemyFactory::instance().registerType(
//	ObjectType::BossSmurf,
//	[](sfPos pos, b2World* world, Player* player) -> std::unique_ptr<BaseEntity> {
//		return std::make_unique<BossSmurf>(pos, world, player);
//	}
//);


BossSmurf::BossSmurf(sfPos pos, b2World* world, Player* player)
	:BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world, player, AnimationSet::Boss)
{
}


