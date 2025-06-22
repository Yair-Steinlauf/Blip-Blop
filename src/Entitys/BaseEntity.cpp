#include "BaseEntity.h"
#include "Constance.h"
BaseEntity::BaseEntity(sf::Texture* tex, sfPos pos, b2World* world)
	:m_world(world)
{
	if (tex)
	{
		m_sprite.setTexture(*tex);
		m_sprite.setPosition(pos);
		auto size = tex->getSize();
		m_sprite.setOrigin(size.x / 2.f, size.y / 2.f);
		initBox2d(pos);
	}

}

void BaseEntity::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);


}

sfPos BaseEntity::getPosition() const
{
	return m_sprite.getPosition();
}

BaseEntity& BaseEntity::setSpritePosition(sfPos pos)
{
	m_sprite.setPosition(pos);
	return *this;
}

BaseEntity::~BaseEntity()
{
	if (m_body && m_world)
		m_world->DestroyBody(m_body);
	m_body = nullptr;
}

b2Body* BaseEntity::getBody() const
{
	return m_body;
}



void BaseEntity::initBox2d(sfPos pos)
{
	initBody(pos);

	//TODO: link body with entity
	//m_body->SetUserData(this);
	//TODO: init poligon
	updatePolygon();

}

void BaseEntity::updatePolygon()
{
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_sprite.getGlobalBounds().width / 2.f / SCALE, m_sprite.getGlobalBounds().height / 2.f / SCALE);
	m_body->CreateFixture(&polygonShape, 1.0f);
}

void BaseEntity::initBody(sfPos& pos)
{
	if (!m_world)
		throw std::runtime_error("Base Entity: No BOX2D World\n");
	b2BodyDef bodyDef;
	bodyDef.position.Set(SFMLToBox2d(pos.x), SFMLToBox2d(pos.y));
	m_body = m_world->CreateBody(&bodyDef);
	if (!m_body)
		throw std::runtime_error("Base Entity: Failed to create Box2D body\n");
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

void BaseEntity::update(float deltaTime) {
	sync();
}

void BaseEntity::setFixture(bool fixedRotation, b2BodyType staticOrDinamic,float linearDamping, float friction, float restitution, float density)
{
	m_body->SetType(staticOrDinamic);
	m_body->SetFixedRotation(fixedRotation);
	m_body->SetLinearDamping(linearDamping);
	m_body->GetFixtureList()->SetFriction(friction);

	m_body->GetFixtureList()->SetRestitution(restitution);

	m_body->GetFixtureList()->SetDensity(density);
	m_body->ResetMassData();
}
/////////////
void BaseEntity::setTextureRect(const sf::IntRect& rect) {
	m_sprite.setTextureRect(rect);
}
