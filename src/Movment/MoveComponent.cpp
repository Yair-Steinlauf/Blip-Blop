#include "Movment/MoveComponent.h"
#include "Movment/MovingState.h"
#include "Movment/GunState.h"
#include "BaseEntity.h"
#include "Constance.h"
#include "PlayerStandMovment.h"

MoveComponent::MoveComponent(BaseEntity& entity)
    : m_entity(entity),m_body(entity.getBody()), m_direction(0.f, 0.f)
{
    sfPos pos = entity.getPosition();
	m_entity.setFixture(true, b2_dynamicBody, 2.5, 0.4f, 0.0f, 1.0f);
    m_state = std::make_unique<PlayerStandMovement>(*this);
}



void MoveComponent::update(float deltaTime) {
    if (m_state) {
        auto newState = m_state->move();
        if (newState) {
            m_state = std::move(newState);
            m_state->enter();
        }
    }
    if (m_gunState) {
        auto newGunState = m_gunState->move();
        if (newGunState) {
            m_gunState = std::move(newGunState);
            m_gunState->enter();
        }
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

void MoveComponent::setGunState(std::unique_ptr<GunState> state) {
    m_gunState = std::move(state);
    if (m_gunState) m_gunState->enter();
}

GunState* MoveComponent::getGunState() const {
    return m_gunState.get();
}