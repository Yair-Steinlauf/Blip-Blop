#pragma once

#include "BaseEntity.h"
class Bullet : public BaseEntity
{
public:
	Bullet(sfPos pos = { 50 , 50 }, b2World* world = nullptr);
	~Bullet() override = default;
	void update(float deltaTime) override;
	void onCollisionEnter(BaseEntity* other) override;
private:
	float m_lifetime = 0.f;
};