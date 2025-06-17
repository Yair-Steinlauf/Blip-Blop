#pragma once
#include "BaseEntity.h"

// Forward declarations
class MovingState;

class MovingEntity : public BaseEntity
{
public:
	MovingEntity(sfPos pos = { 0,0 }, b2World* world = nullptr);
	void setDirection(sfPos direction);
	~MovingEntity() override = default;
	void update(float deltaTime) override;
	virtual void movment();
protected:
	sfPos m_direction;
	std::unique_ptr<MovingState> m_movement;
	float m_speed = 100.f; // Default speed
	void initBox2d(sfPos pos) override;
};