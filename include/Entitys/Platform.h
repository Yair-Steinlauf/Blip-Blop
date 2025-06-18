#pragma once

#include "StaticEntity.h"

class Platform : public StaticEntity
{
public:
	Platform(sfPos pos = { 50 , 50}, b2World* world = nullptr, sf::Vector2f size = { 64, 32 });
	~Platform() override = default;
protected:
	void initBox2d(sfPos pos, sf::Vector2f size);
};