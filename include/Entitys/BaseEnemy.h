#pragma once
#include "BaseEntity.h"
#include "MoveComponent.h"
class Player;

class BaseEnemy : public BaseEntity
{
public:
	BaseEnemy(sf::Texture* tex = nullptr, sfPos pos = { 0,0 }, b2World* world = nullptr, Player* player = nullptr);
	virtual ~BaseEnemy() override = default;
	virtual void update(float deltaTime);
protected:
	Player* m_player = nullptr;
	MoveComponent m_moveComponent;

};