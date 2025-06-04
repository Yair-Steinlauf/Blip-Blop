#pragma once
#include "BaseEnemy.h"

template <typename MovementStrategy, typename AttackStrategy>
class TemplateEnemy : public BaseEnemy
{
public:
	using BaseEnemy::BaseEnemy;
	TemplateEnemy() {
		m_movement = std::make_unique<MovementStrategy>();
		m_attackStrategy = std::make_unique<AttackStrategy>();
	}
	~TemplateEnemy() override = default;
};

static auto registerIt = Factory<BaseEnemy>::instance().registerType(
	ObjectType::Player,
	[]() -> std::unique_ptr<BaseEnemy>
	{
		return std::make_unique<TemplateEnemy<MoveStrategy, AttackStrategy>>();
	}
);
