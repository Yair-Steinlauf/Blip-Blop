
#include "Enemys/PresentSmurf.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "DataLoader.h"
#include <bullet.h>

static bool regPresentSmurf = EnemyFactory::instance().registerType(
	ObjectType::PresentSmurf,
	[](sfPos pos, b2World* world, Player* player) -> std::unique_ptr<BaseEntity> {
		return std::make_unique<PresentSmurf>(pos, world, player);
	}
);

PresentSmurf::PresentSmurf(sfPos pos, b2World* world, Player* player)
	: BaseEnemy(&DataLoader::getInstance().getP2Texture(ObjectType::characterSprite), pos, world, player, AnimationSet::PresentEnemy)

{
	m_moveComponent.setHealth(1);
}

void PresentSmurf::onCollisionEnter(BaseEntity* other)
{
	if (auto* bullet = dynamic_cast<Bullet*>(other)) {

		m_moveComponent.takeDamage(1);
	}
	if (auto* player = dynamic_cast<Player*>(other)) {
		player->addLife(-2);
		m_moveComponent.setHealth(0);
	}
}