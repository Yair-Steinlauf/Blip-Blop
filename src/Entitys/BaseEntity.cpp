#include "BaseEntity.h"
#include "Constance.h"

BaseEntity::BaseEntity(sfPos pos, b2World* world)
	:m_world(world)
{
	m_sprite.setPosition(pos);
}

void BaseEntity::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sfPos BaseEntity::getPosition() const
{
	 return m_sprite.getPosition();
}

BaseEntity::~BaseEntity()
{
	if (m_body && m_world)
		m_world->DestroyBody(m_body);
	m_body = nullptr;
}

void BaseEntity::initBox2d(sfPos pos, b2World* world)
{
	if (!world)
		throw std::runtime_error("Base Entity: No BOX2D World\n");
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x / SCALE, pos.y / SCALE);
	m_body = world->CreateBody(&bodyDef);
	if (!m_body)
		throw std::runtime_error("Base Entity: Failed to create Box2D body\n");

	//TODO: link body with entity
	//m_body->SetUserData(this);
	//TODO: init poligon
}

void BaseEntity::initSprite(sf::Texture& tex)
{
	m_sprite.setTexture(tex);
	auto size = tex.getSize();
	m_sprite.setOrigin(size.x / 2.f, size.y / 2.f);
}

void BaseEntity::sync()
{
	if (!m_body) 
		throw std::runtime_error("No Box2d Body!\n");
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle();

	m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
	m_sprite.setRotation(angle * 180 / b2_pi);
}

