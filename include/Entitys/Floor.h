#pragma once

#include "StaticEntity.h"

class Floor : public StaticEntity
{
public:
	Floor(sfPos pos = { 50 , 50}, b2World* world = nullptr);
	~Floor() override = default;
protected:
	sf::Texture& createInvisibleTexture();
	void createVisibleTexture();
	void  initBox2d(sfPos pos) override;
};