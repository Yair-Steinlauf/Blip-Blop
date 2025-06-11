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
	BaseEntity(sfPos pos = {0,0}, b2World* world = nullptr);
	virtual void draw(sf::RenderWindow& window) const;
	virtual void update(float deltaTime) {}//TODO: function update
	sfPos getPosition() const;
	virtual ~BaseEntity();
protected:
	sf::Sprite m_sprite;
	b2Body* m_body = nullptr;
	b2World* m_world = nullptr;
	void initBox2d(sfPos pos, b2World* );
	void initSprite(sf::Texture& tex);
	void sync();

};

