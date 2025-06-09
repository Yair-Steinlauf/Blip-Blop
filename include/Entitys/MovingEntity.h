#pragma once
#include "BaseEntity.h"

// Forward declarations
class MovingState;

class MovingEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	MovingEntity() = default;
	void setDirection(sfPos direction);
	~MovingEntity() override = default;
	void update(float deltaTime) override;
	virtual void movment(float deltaTime, const sf::Event& event = sf::Event());
protected:
	sfPos m_direction;
	std::unique_ptr<MovingState> m_movement;
	float m_speed = 100.f; // Default speed

};