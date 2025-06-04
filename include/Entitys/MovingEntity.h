#pragma once
#include "BaseEntity.h"
#include "MoveStrategy.h"

using MovementPtr = std::unique_ptr<MoveStrategy>;


class MovingEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	MovingEntity() = default;
	void move(float deltaTime) {}; //TODO set direction
	~MovingEntity() override = default;
private:
	MovementPtr m_movement;
};