#pragma once
#include <memory>
#include "BaseEntity.h"

class ShootingStrategy {
public:
    virtual ~ShootingStrategy() = default;
    virtual std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f entityPos, sf::Vector2f direction, b2World* world) = 0;
};
