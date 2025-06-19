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
#include "Constance.h"


//==============Forward declarations============


class BaseEntity
{
public:
	BaseEntity(sfPos pos = {0,0}, b2World* world = nullptr);
	virtual void draw(sf::RenderWindow& window) const;
	virtual void update(float deltaTime) {}//TODO: function update
	sfPos getPosition() const;
	BaseEntity& setSpritePosition(sfPos pos);
	virtual ~BaseEntity();
protected:
	sf::Sprite m_sprite;
	b2Body* m_body = nullptr;
	b2BodyDef m_bodyDef; 
	b2World* m_world = nullptr;
	b2PolygonShape m_polygonShape;
	b2Fixture* m_fixture = nullptr;
	virtual void initBox2d(sfPos pos);
	void initSprite(sf::Texture& tex);
	void sync();

};

