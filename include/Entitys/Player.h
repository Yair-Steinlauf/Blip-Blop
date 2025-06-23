#pragma once
#include "BaseEntity.h"
#include "Movment/MoveComponent.h"
#include "Subject.h"
#include "Movment/MovingState.h"
#include "Movment/GunMovment/GunState.h"

class Player : public BaseEntity, public Subject
{
public:
	Player(sfPos pos = { 0,0 }, b2World* world = nullptr);
	~Player() override = default;
	void update(float deltaTime) override;
	void setMouseWorldPosition(sf::Vector2f m_mousePos);
private:
	MoveComponent m_moveComponent;
};
