#pragma once
#include <SFML/Graphics.hpp>
#include <memory>


class BaseEntity
{
public:
	BaseEntity() = default;
	virtual void draw() const = 0;
	virtual void update(float deltaTime) = 0;

	virtual ~BaseEntity() = default;
private:
	sf::Sprite m_sprite;
}