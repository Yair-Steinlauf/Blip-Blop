#include <memory>
#include "BaseEnemy.h"
#include "Smurf.h"
#include "DataLoader.h"
#include "Factory/Factory.h"
#include "EnemyMovmentState.h"

//TODO: Register the Smurf enemy type in the factory
//static auto regSmurf = Factory<BaseEntity>::instance().registerType(
//	ObjectType::SMURF,
//	[]() -> std::unique_ptr<BaseEntity>
//	{
//		return std::make_unique<Smurf>();
//	}
//);


Smurf::Smurf(sfPos pos)
	:BaseEnemy()
{
	m_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::SMURF));
	m_sprite.setPosition(pos);
	m_movement = std::make_unique<EnemyMovementState>(*this);
}


