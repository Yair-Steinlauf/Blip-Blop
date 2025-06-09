#pragma once
#include "BaseEnemy.h"
#include "Factory.h"

template <typename MovementStrategy>//, typename AttackStrategy>
class TemplateEnemy : public BaseEnemy
{
public:
	using BaseEnemy::BaseEnemy;
	TemplateEnemy(ObjectType type) {
		//get type, load texture, set movement strategy, etc.
		m_sprite.setTexture(DataLoader::getInstance().getP2Texture(type));
		m_movement = std::make_unique<MovementStrategy>();
		//m_attackStrategy = std::make_unique<AttackStrategy>();
	}
	void update(float dt) override {
		MovingEntity::movment();
		MovingEntity::update(dt);
	}
	~TemplateEnemy() override = default;
};
//register to factory in the cpp file!

