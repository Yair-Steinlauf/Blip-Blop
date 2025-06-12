#pragma once
#include "AttackingEntity.h"

class Player : public AttackingEntity
{
public:
	Player(sfPos pos = { 0,0 }, b2World* world = nullptr);
	~Player() override = default;

private:
	
};
