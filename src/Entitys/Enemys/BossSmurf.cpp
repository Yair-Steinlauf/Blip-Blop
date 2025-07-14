#include "BossSmurf.h"
#include "EnemyFactory.h"
#include "Player.h" 
#include "DataLoader.h"









BossSmurf::BossSmurf(sfPos pos, b2World* world, Player* player)
	:BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world, player, AnimationSet::Boss)
{
}


