#pragma once

#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)
#include <SFML/Graphics.hpp>
#include <memory>
#include "Factory.h"
#include "DataLoader.h"
#include "Constance.h"
#include "GameAnimations.h"



class EntityVisitor;


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
	b2World* getWorld() const;

	void setTextureRect(const sf::IntRect& rect, float FIXTURE_WIDTH, float FIXTURE_HEIGHT);
	void setDirection(sf::Vector2f direction);
	sf::Vector2f getDirection();
	void setFixtureForMov();
	void rotateToDirection(const sf::Vector2f& direction);
	void setTextureRect(const sf::IntRect& rect);
	bool shouldBeRemoved() const;
	void markForRemoval();
	virtual void onCollisionEnter(BaseEntity* other) {}
	virtual void onCollisionExit(BaseEntity* other) {}

protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_direction;
	b2Body* m_body = nullptr;
	b2World* m_world = nullptr;
	bool m_shouldBeDestroyed = false;
	virtual void initBox2d(sfPos pos);
	void updatePolygon();
	void updatePolygonWithSize(float FIXTURE_WIDTH, float FIXTURE_HEIGHT);
	void initBody(sfPos& pos);
	void sync();

};

