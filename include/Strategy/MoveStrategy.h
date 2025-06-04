#pragma once
#include <BaseEntity.h>

class MoveStrategy {
public:
	MoveStrategy();

	virtual void move(BaseEntity& entity) = 0;

};