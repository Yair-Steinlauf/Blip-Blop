#pragma once

#include "ShootingStrategy.h"
#include <vector>
#include <memory>
#include <SFML/System.hpp>

class TripleShotStrategy : public ShootingStrategy {
public:
    std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f entityPos,
        sf::Vector2f direction, b2World* world) override;

private:
    sf::Vector2f rotate(const sf::Vector2f& v, float degrees);
};
