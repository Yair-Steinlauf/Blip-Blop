#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Constance.h"
#include "Entitys/BaseEntity.h"

class MovingState;
class MoveComponent {
public:
    MoveComponent(BaseEntity& entity, std::unique_ptr<MovingState> state);
    void update(float deltaTime);
    void setDirection(sf::Vector2f direction);
    sfPos getDirection() const;
    void setVelocity(float x, float y);
    void applyJumpImpulse(float force);
    bool checkIsGrounded() const;
    void setSpeed(float speed);
    float getSpeed() const;
    const BaseEntity& getEntity()const;
    void setState(std::unique_ptr<MovingState> state);
    MovingState* getState() const;
    int getHealth() const;
    void setHealth(int life);
    void takeDamage(int amount);

private:
    BaseEntity& m_entity;
    sf::Vector2f m_direction;
    float m_speed = 100.f;
    std::unique_ptr<MovingState> m_state;
    int m_health = 5;
}; 