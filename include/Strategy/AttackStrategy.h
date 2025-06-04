#pragma once
#include "Strategy.h"

//================Forward declaration=======================
class AttackingEntity;


class AttackStrategy :public Strategy{
public:
	virtual void attack(AttackingEntity* entity) {}//TODO: function
};