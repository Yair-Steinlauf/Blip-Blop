#pragma once
#include "MovingEntity.h"

using AttackPtr = std::unique_ptr<AttackStrategy>;

class AttackingEntity : public MovingEntity
{
public:
	using MovingEntity::MovingEntity;
	StaticEntity() = default;
	~StaticEntity() override = default;

	virtual void attack();
private:
	AttackPtr m_attackStrategy;
}
