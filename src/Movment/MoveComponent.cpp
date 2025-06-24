#include "Movment/MoveComponent.h"
#include "Movment/MovingState.h"
#include "Movment/GunMovment/Gun.h"
#include "BaseEntity.h"
#include "Constance.h"
#include "PlayerStandMovment.h"

MoveComponent::MoveComponent(BaseEntity& entity)
    : m_entity(entity),m_body(entity.getBody()), m_direction(0.f, 0.f)
{
    sfPos pos = entity.getPosition();
	m_entity.setFixture(true, b2_dynamicBody, 2.5, 0.4f, 0.0f, 1.0f);
    m_state = std::make_unique<PlayerStandMovement>(*this);
    m_gun = std::make_unique<Gun>(*this);
}



void MoveComponent::update(float deltaTime) {

    if (m_state) {
        auto newState = m_state->move();
        if (newState) {
            m_state = std::move(newState);
            m_state->enter();
        }
    }
    if (m_gun) {
        Direction direction = m_gun->move(m_mousePos, m_entityPos);
        if (static_cast<int>(direction) != 0)
            m_gun->enter(direction);
    }
    //speed limit
    float maxVelocity = 2500.0f; 
    b2Vec2 currentVel = m_body->GetLinearVelocity();

    if (std::abs(currentVel.x) < maxVelocity) {
        b2Vec2 force(m_direction.x * m_speed, 0); 
        m_body->ApplyForceToCenter(force, true);
    }
    
}

void MoveComponent::setDirection(sf::Vector2f direction) {
    sf::Vector2f stand = { 0.f, 0.f };
    m_direction = direction;
    if (direction != stand)
        m_lastDirection = direction;
}

sf::Vector2f MoveComponent::getDirection() {
    return m_lastDirection;
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

Gun* MoveComponent::getGunState() const {
    return m_gun.get();
}

BaseEntity& MoveComponent::getEntity() {
    return m_entity;
}

void MoveComponent::setMouseWorldPosition(sf::Vector2f mousePos) {
    m_mousePos = mousePos;
}

sf::Vector2f MoveComponent::getMouseWorldPosition() {
    return m_mousePos;
}

void MoveComponent::setEntityPos(sf::Vector2f entityPos) {
    m_entityPos = entityPos;
}

sf::Vector2f MoveComponent::getEntityPos() {
    return m_entityPos;
}