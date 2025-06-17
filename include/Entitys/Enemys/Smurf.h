#pragma once

#include "BaseEnemy.h"

class Smurf : public BaseEnemy
{
public:
	Smurf(sfPos pos = { 50,50 });
	~Smurf() override = default;
	void update(float deltaTime) override
	{
		BaseEnemy::update(deltaTime);
		movment();
	}
};