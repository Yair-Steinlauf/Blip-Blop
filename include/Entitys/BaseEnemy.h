#pragma once
#include "BaseEntity.h"
#include "MoveComponent.h"
#include "Animator.h"

class Player;

class BaseEnemy : public BaseEntity
{
public:
	BaseEnemy(sf::Texture* tex = nullptr, sfPos pos = { 0,0 }, b2World* world = nullptr, Player* player = nullptr, AnimationSet animationSet = AnimationSet());
	virtual ~BaseEnemy() override = default;
	virtual void update(float deltaTime);
protected:
	Player* m_player = nullptr;
	MoveComponent m_moveComponent;
	AnimationSet m_animationSet;
	Animator m_animation;

};