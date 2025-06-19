//#include <memory>
//#include "BaseEnemy.h"
//#include "Smurf.h"
//#include "DataLoader.h"
//#include "Factory/Factory.h"
//#include "EnemyMovmentState.h"
//
////TODO: Register the Smurf enemy type in the factory
////static auto regSmurf = Factory<BaseEntity>::instance().registerType(
////	ObjectType::SMURF,
////	[]() -> std::unique_ptr<BaseEntity>
////	{
////		return std::make_unique<Smurf>();
////	}
////);
//
//
//Smurf::Smurf(sfPos pos, b2World* world)
//	:BaseEnemy()
//{
//	m_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::SMURF));
//	m_sprite.setPosition(pos);
//	m_moveComponent = std::make_unique<MoveComponent>(*this, world);
//	m_moveComponent->setState(std::make_unique<EnemyMovementState>(*m_moveComponent));
//}
//
//void Smurf::update(float deltaTime)
//{
//	if (m_moveComponent)
//		m_moveComponent->update(deltaTime);
//}
//TODO: 