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

//void BaseEntity::updatePolygon()
//{
//	b2PolygonShape polygonShape;
//	polygonShape.SetAsBox(m_sprite.getGlobalBounds().width / 2.f / SCALE, m_sprite.getGlobalBounds().height / 2.f / SCALE);
//	m_body->CreateFixture(&polygonShape, 1.0f);
//}
//void BaseEntity::updatePolygon()
//{
//	if (!m_body) return;
//
//	/* 1. מוחקים את כל ה-fixtures הקיימים */
//	while (b2Fixture* f = m_body->GetFixtureList())
//		m_body->DestroyFixture(f);
//
//	/* 2. בונים אחד חדש על-פי הגבולות הנוכחיים של הספרייט */
//	const auto bounds = m_sprite.getGlobalBounds();
//
//	b2PolygonShape shape;
//	shape.SetAsBox(bounds.width / 2.f / SCALE,
//		bounds.height / 2.f / SCALE);
//
//	b2FixtureDef fd;
//	fd.shape = &shape;
//	fd.density = 1.f;
//	fd.friction = 0.3f;
//	fd.restitution = 0.f;
//
//	m_body->CreateFixture(&fd);
//}
void BaseEntity::updatePolygon()
{
	if (!m_body) return;

	// 1. מוחקים את כל ה-fixtures הקיימים
	while (b2Fixture* f = m_body->GetFixtureList())
		m_body->DestroyFixture(f);

	const float FIXTURE_WIDTH = 40.f;
	const float FIXTURE_HEIGHT = 28.f;

	b2PolygonShape shape;
	shape.SetAsBox(FIXTURE_WIDTH / 2.f / SCALE,
		FIXTURE_HEIGHT / 2.f / SCALE);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.f;
	fd.friction = 0.3f;
	fd.restitution = 0.f;

	m_body->CreateFixture(&fd);
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
//void BaseEntity::setTextureRect(const sf::IntRect& rect)
//{
//	/* 1. חותכים את הספרייט         */
//	m_sprite.setTextureRect(rect);
//
//	/* 2. מיישרים שוב למרכז (חשוב!) */
//	m_sprite.setOrigin(rect.width / 2.f,
//		rect.height / 2.f);
//
//	/* 3. מעדכנים את גוף-הפיזיקה    */
//	if (m_body)            // לוודא שהגוף כבר קיים
//	{
//		/* מוחקים את ה-fixture הישן (יכול להיות יותר מאחד) */
//		while (b2Fixture* f = m_body->GetFixtureList())
//			m_body->DestroyFixture(f);
//
//		/* בונים fixture חדש בגודל הפריים הנוכחי        */
//		b2PolygonShape poly;
//		const auto bounds = m_sprite.getGlobalBounds();
//		poly.SetAsBox(bounds.width / 2.f / SCALE,
//			bounds.height / 2.f / SCALE);
//
//		b2FixtureDef fd;
//		fd.shape = &poly;
//		fd.density = 1.f;
//		fd.friction = 0.3f;
//		fd.restitution = 0.f;
//
//		m_body->CreateFixture(&fd);
//	}
//}

void BaseEntity::setTextureRect(const sf::IntRect& rect)
{
	/* חיתוך הספרייט + Origin חדש */
	m_sprite.setTextureRect(rect);
	m_sprite.setOrigin(rect.width / 2.f,
		rect.height / 2.f);

	/* התאמת ה-fixture – שימוש חוזר בפונקציה שלך */
	updatePolygon();
}
