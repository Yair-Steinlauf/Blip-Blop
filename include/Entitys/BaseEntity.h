#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Factory.h"


class BaseEntity
{
public:
	BaseEntity() = default;
	virtual void draw() const = 0;
	virtual void update(float deltaTime) = 0;

	virtual ~BaseEntity() = default;
protected:
	sf::Sprite m_sprite;
};