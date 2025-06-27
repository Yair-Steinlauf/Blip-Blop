#include "Movment/MoveComponent.h"
#include "Movment/MovingState.h"
#include "Movment/GunMovment/Gun.h"
#include "BaseEntity.h"
#include "Constance.h"

MoveComponent::MoveComponent(BaseEntity& entity, std::unique_ptr<MovingState> state)
    : m_entity(entity), m_direction(0.f, 0.f), m_state(std::move(state))
{
    sfPos pos = entity.getPosition();
  
    m_entity.setFixture(true, b2_dynamicBody, 2.5, 0.4f, 0.0f, 1.0f);
}



void MoveComponent::update(float deltaTime) {

    if (m_state) {
        auto newState = m_state->move();
        if (newState) {
            m_state = std::move(newState);
            m_state->enter();
        }
    }
    //speed limit
    float maxVelocity = 2500.0f; 
    b2Vec2 currentVel = m_entity.getBody()->GetLinearVelocity();

    if (std::abs(currentVel.x) < maxVelocity) {
        b2Vec2 force(m_direction.x * m_speed, 0); 
        m_entity.getBody()->ApplyForceToCenter(force, true);
    }
    
}

void MoveComponent::setDirection(sf::Vector2f direction) {
    m_direction = direction;
}

sfPos MoveComponent::getDirection() const
{
    return m_direction;
}

void MoveComponent::setVelocity(float x, float y) {
    m_entity.getBody()->SetLinearVelocity(b2Vec2(x, y));
}

void MoveComponent::applyJumpImpulse(float force) {
    if (checkIsGrounded()) {
        b2Vec2 jumpImpulse(0, -force);
        m_entity.getBody()->ApplyLinearImpulseToCenter(jumpImpulse, true);
    }
}

bool MoveComponent::checkIsGrounded() const {
    return std::abs(m_entity.getBody()->GetLinearVelocity().y) == 0;
}

void MoveComponent::setSpeed(float speed) {
    m_speed = speed;
}

float MoveComponent::getSpeed() const {
    return m_speed;
}

const BaseEntity& MoveComponent::getEntity() const
{
    return m_entity;
}

void MoveComponent::setState(std::unique_ptr<MovingState> state) {
    m_state = std::move(state);
    if (m_state) m_state->enter();
}

MovingState* MoveComponent::getState() const {
    return m_state.get();
} 

int MoveComponent::getHealth() const {
    return m_health; 
}

void MoveComponent::setHealth(int life){
    m_health = life;
}

void MoveComponent::takeDamage(int amount) {
    m_health -= amount;
    if (m_health < 0) {
        m_health = 0;
        m_entity.markForRemoval();
    }
}
