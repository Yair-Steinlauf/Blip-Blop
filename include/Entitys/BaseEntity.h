#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Factory.h"

//==============Forward declarations============

using sfPos = sf::Vector2f;

class BaseEntity
{
public:
	BaseEntity() = default;
	virtual void draw(sf::RenderWindow& window) const;
	virtual void update(float deltaTime) {}//TODO: function update

	virtual ~BaseEntity() = default;
protected:
	sf::Sprite m_sprite;
};