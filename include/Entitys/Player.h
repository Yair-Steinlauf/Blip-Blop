#pragma once
#include "AttackingEntity.h"

class Player : public AttackingEntity
{
public:
	using AttackingEntity::AttackingEntity;
	Player();
	~Player() override = default;

private:
	
};
