#pragma once

#include "StaticEntity.h"

class Floor : public StaticEntity
{
public:
	Floor(sfPos pos = { 0 , SCREEN_HEIGHT }, b2World* world = nullptr);
	~Floor() override = default;
protected:
	sf::Texture& createInvisibleTexture();
};