#pragma once
#include "AttackingEntity.h"

class BaseEnemy : public AttackingEntity
{
public:
	using AttackingEntity::AttackingEntity;
	BaseEnemy() = default;
	~BaseEnemy() override = default;
};