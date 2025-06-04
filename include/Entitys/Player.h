#pragma once
#include "AttackingEntity"

class Player : public AttackingEntity
{
public:
	using AttackingEntity::AttackingEntity;
	Player() = default;
	~Player() override = default;
}
