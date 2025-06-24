#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Constance.h"
#include "Entitys/BaseEntity.h"

class MovingState;
class Gun;
class MoveComponent {
public:
    MoveComponent(BaseEntity& entity);
    void update(float deltaTime);
    void setDirection(sf::Vector2f direction);
    void setVelocity(float x, float y);
    void applyJumpImpulse(float force);
    bool checkIsGrounded() const;
    void setSpeed(float speed);
    float getSpeed() const;
    void setState(std::unique_ptr<MovingState> state);
    MovingState* getState() const;

private:
    BaseEntity& m_entity;
    sf::Vector2f m_direction;
    float m_speed = 10.f;
    std::unique_ptr<MovingState> m_state;
}; 