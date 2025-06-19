#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Constance.h"
#include "Entitys/BaseEntity.h"

class MovingState;
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
    //TODO: add animation system interface here?
private:
    BaseEntity& m_entity;
    b2Body* m_body = nullptr;
    sf::Vector2f m_direction;
    float m_speed = 10000000000.f;
    std::unique_ptr<MovingState> m_state;
    void initBox2d(sfPos pos);
}; 