#pragma once
#include "AttackingEntity.h"
#include "Subject.h"
class Player : public AttackingEntity , public Subject
{
public:
	Player(sfPos pos = { 0,0 }, b2World* world = nullptr);
	~Player() override = default;

private:
	
};
