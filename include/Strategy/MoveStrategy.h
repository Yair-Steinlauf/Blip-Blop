#pragma once
#include "Strategy.h"

class MoveStrategy : public Strategy{
public:
	MoveStrategy() = default;
	virtual void move(BaseEntity& entity) = 0;

};