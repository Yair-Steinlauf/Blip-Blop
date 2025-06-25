#pragma once

#include "BaseEntity.h"
class bullet : public BaseEntity
{
public:
	bullet(sfPos pos = { 50 , 50 }, b2World* world = nullptr);
	~bullet() override = default;
protected:
	void initBox2d(sfPos pos, sf::Vector2f size);
};