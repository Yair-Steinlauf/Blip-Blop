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
    sf::Vector2f getDirection();
    void setVelocity(float x, float y);
    void applyJumpImpulse(float force);
    bool checkIsGrounded() const;
    void setSpeed(float speed);
    float getSpeed() const;
    void setState(std::unique_ptr<MovingState> state);
    MovingState* getState() const;
    //void setGunState(std::unique_ptr<Gun> state);
    Gun* getGunState() const;
    //TODO: add animation system interface here?
    BaseEntity& getEntity();
    void setMouseWorldPosition(sf::Vector2f mousePos);
    sf::Vector2f getMouseWorldPosition();
    void setEntityPos(sf::Vector2f entityPos);
    sf::Vector2f getEntityPos();

private:
    BaseEntity& m_entity;
    b2Body* m_body = nullptr;
    sf::Vector2f m_direction;
    sf::Vector2f m_lastDirection;
    sf::Vector2f m_entityPos;
    float m_speed = 10.f;
    std::unique_ptr<MovingState> m_state;
    std::unique_ptr<Gun> m_gun;
    sf::Vector2f m_mousePos;
}; 