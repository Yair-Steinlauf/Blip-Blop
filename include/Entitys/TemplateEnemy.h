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
