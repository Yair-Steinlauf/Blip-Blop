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
class EntityVisitor; // Forward declaration


class BaseEntity
{
public:
	BaseEntity(sf::Texture* tex = nullptr ,sfPos pos = {0,0}, b2World* world = nullptr);
	virtual void draw(sf::RenderWindow& window) const;
	virtual void update(float deltaTime);
	void setFixture(bool fixedRotation, b2BodyType staticOrDinamic, float linearDamping, float friction, float restitution, float density);
	sfPos getPosition() const;
	BaseEntity& setSpritePosition(sfPos pos);
	virtual ~BaseEntity();
	b2Body* getBody() const;
protected:
	sf::Sprite m_sprite;
	b2Body* m_body = nullptr;
	b2World* m_world = nullptr;
	virtual void initBox2d(sfPos pos);
	void updatePolygon();
	void initBody(sfPos& pos);
	void sync();

};

