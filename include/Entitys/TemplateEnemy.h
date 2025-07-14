#pragma once
#include "BaseEnemy.h"
#include "Factory.h"

template <typename MovementStrategy>
class TemplateEnemy : public BaseEnemy
{
public:
	using BaseEnemy::BaseEnemy;
	TemplateEnemy(ObjectType type) {

		m_sprite.setTexture(DataLoader::getInstance().getP2Texture(type));
		m_movement = std::make_unique<MovementStrategy>();

	}
	void update(float dt) override {
		MovingEntity::movment();
		MovingEntity::update(dt);
	}
	~TemplateEnemy() override = default;
};


