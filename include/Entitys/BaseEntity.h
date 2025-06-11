#pragma once
// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)
#include <SFML/Graphics.hpp>
#include <memory>
#include "Factory.h"
#include "DataLoader.h"

//==============Forward declarations============

using sfPos = sf::Vector2f;

class BaseEntity
{
public:
	BaseEntity() = default;
	virtual void draw(sf::RenderWindow& window) const;
	virtual void update(float deltaTime) {}//TODO: function update
	sfPos getPosition() const;
	virtual ~BaseEntity() = default;
protected:
	sf::Sprite m_sprite;
};