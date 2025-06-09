#pragma once
#include "Strategy.h"
//================Forward declaration=======================
class MovingEntity;

class MoveStrategy : public Strategy {
public:
	MoveStrategy(float speed = 600.f) : m_speed(speed) {}
	virtual ~MoveStrategy() = default;

	virtual sf::Vector2f setDirection(MovingEntity& entity, float deltaTime) = 0;

	void setSpeed(float speed) { m_speed = speed; }
	float getSpeed() const { return m_speed; }

protected:
	float m_speed; 
};