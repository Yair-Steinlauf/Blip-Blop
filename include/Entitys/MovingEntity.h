#pragma once
#include "BaseEntity.h"
using MovementPtr = std::unique_ptr<Movement>;


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