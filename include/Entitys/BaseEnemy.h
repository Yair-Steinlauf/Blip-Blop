#pragma once
#include "BaseEntity.h"
#include "MoveComponent.h"
#include "Animator.h"

class Player;


class BaseEnemy : public BaseEntity
{
public:
	BaseEnemy(sf::Texture* tex = nullptr, sfPos pos = { 0,0 }, b2World* world = nullptr, Player* player = nullptr, AnimationSet animationSet = AnimationSet());
	virtual ~BaseEnemy() override;
	virtual void update(float deltaTime);
	void addLife(int life);
	void onCollisionEnter(BaseEntity* other) override;
	//void onCollisionExit(BaseEntity* other);
	static int getAliveCount();
	static int getTotalKills();
protected:
	static inline int m_alive = 0;
	static inline int m_totalKills = 0;

	Player* m_player = nullptr;
	MoveComponent m_moveComponent;
	AnimationSet m_animationSet;
	Animator m_animation;
	bool m_isExploding = false;
	float m_explosionTime = 0.0f;
	float m_frameTime = 0.1f;
	std::size_t m_currentExplosionFrame = 0;
	const std::size_t TOTAL_EXPLOSION_FRAMES = 7;

	void updateExplosionAnimation(float deltaTime);
	void startExplosion();

	static inline int m_counter = 0;   //  C++17 inline static
};