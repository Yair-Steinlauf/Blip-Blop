#pragma once
#include "AttackingEntity.h"
#include "MovingEntity.h"
#include "BaseEntity.h"


class Player : public AttackingEntity, MovingEntity, BaseEntity
{
public:
	Player();
	~Player() override = default;

private:
	
};
