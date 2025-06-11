#pragma once
#include "AttackingEntity.h"
#include "MovingEntity.h"
#include "BaseEntity.h"


class BaseEnemy : public AttackingEntity, MovingEntity, BaseEntity
{
public:
	BaseEnemy() = default;
	~BaseEnemy() override = default;
};