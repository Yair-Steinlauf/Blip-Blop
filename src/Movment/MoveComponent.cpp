#include "Movment/MoveComponent.h"
#include "Movment/MovingState.h"
#include "BaseEntity.h"
#include "Constance.h"
#include "PlayerStandMovment.h"

MoveComponent::MoveComponent(BaseEntity& entity)
    : m_entity(entity),m_body(entity.getBody()), m_direction(0.f, 0.f), m_speed(100.f)
{
    sfPos pos = entity.getPosition();
    m_body->SetType(b2_dynamicBody);
    m_body->SetFixedRotation(true);
    m_body->SetLinearDamping(2.5f);
    m_body->GetFixtureList()->SetFriction(0.0f);

    m_body->GetFixtureList()->SetRestitution(0.0f);

    m_body->GetFixtureList()->SetDensity(1.0f);
	m_body->ResetMassData();
    m_state = std::make_unique<PlayerStandMovement>(*this);
}

void MoveComponent::initBox2d(sfPos pos)
{

    //b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    //bodyDef.position.Set(pos.x / SCALE, pos.y / SCALE);
    //m_body = m_world->CreateBody(&bodyDef);
    //m_polygonShape.SetAsBox(25.f / SCALE, 25.f / SCALE); // דוגמה, אפשר לשפר לפי sprite
    //b2FixtureDef fix;
    //fix.shape = &m_polygonShape;
    //fix.density = 1.0f;
    //fix.friction = 0.8f;
    //fix.restitution = 0.0f;
    //m_fixture = m_body->CreateFixture(&fix);

}

void MoveComponent::update(float deltaTime) {
    if (m_state) {
        auto newState = m_state->move();
        if (newState) {
            m_state = std::move(newState);
            m_state->enter();
        }
    }

    float maxVelocity = 25.0f; // או מהירות שתראה טבעית
    b2Vec2 currentVel = m_body->GetLinearVelocity();

    //if (std::abs(currentVel.x) < maxVelocity) {
        b2Vec2 force(m_direction.x * m_speed, 0); 
        m_body->ApplyForceToCenter(force, true);
    //}
    //b2Vec2 force(m_direction.x * m_speed , 0);
    //m_body->ApplyForceToCenter(force, true);
    //// עדכון מיקום ה-entity לפי הפיזיקה
    b2Vec2 pos = m_body->GetPosition();
    m_entity.setSpritePosition({ pos.x * SCALE, pos.y * SCALE });
    //TODO: call animation system here
    
}

void MoveComponent::setDirection(sf::Vector2f direction) {
    m_direction = direction;
}

void MoveComponent::setVelocity(float x, float y) {
    m_body->SetLinearVelocity(b2Vec2(x, y));
}

void MoveComponent::applyJumpImpulse(float force) {
    if (checkIsGrounded()) {
        b2Vec2 jumpImpulse(0, -force);
        m_body->ApplyLinearImpulseToCenter(jumpImpulse, true);
    }
}

bool MoveComponent::checkIsGrounded() const {
    return std::abs(m_body->GetLinearVelocity().y) == 0;
}

void MoveComponent::setSpeed(float speed) {
    m_speed = speed;
}

float MoveComponent::getSpeed() const {
    return m_speed;
}

void MoveComponent::setState(std::unique_ptr<MovingState> state) {
    m_state = std::move(state);
    if (m_state) m_state->enter();
}

MovingState* MoveComponent::getState() const {
    return m_state.get();
} 