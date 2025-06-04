#pragma once
#include "BaseEntity.h"
#include "MoveStrategy.h"

using MovementPtr = std::unique_ptr<MoveStrategy>;


class MovingEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	MovingEntity() = default;
	virtual void move(float deltaTime) = 0; // Pure virtual function for movement behavior
	~MovingEntity() override = default;
private:
	MovementPtr m_movement;
};