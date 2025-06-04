#pragma once
#include "MovingEntity.h"
#include "Strategy/AttackStrategy.h"

using AttackPtr = std::unique_ptr<AttackStrategy>;

class AttackingEntity : public MovingEntity
{
public:
	using MovingEntity::MovingEntity;
	AttackingEntity() = default;
	~AttackingEntity() override = default;

	//virtual void attack();
protected:
	AttackPtr m_attackStrategy;
};
