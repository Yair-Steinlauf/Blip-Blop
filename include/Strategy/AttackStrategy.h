#pragma once
#include <BaseEntity.h>

class AttackStrategy {
public:
	AttackStrategy();

	virtual void attack(BaseEntity& entity) = 0;

};