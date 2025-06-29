
#include "Enemys/PresentSmurf.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "DataLoader.h"

static bool regPresentSmurf = EnemyFactory::instance().registerType(
	ObjectType::PresentSmurf,
	[](sfPos pos, b2World* world, Player* player) -> std::unique_ptr<BaseEntity> {
		return std::make_unique<PresentSmurf>(pos, world, player);
	}
);

PresentSmurf::PresentSmurf(sfPos pos, b2World* world, Player* player)
	: BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world, player, AnimationSet::PresentEnemy)

{
}

