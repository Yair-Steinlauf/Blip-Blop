#pragma once

#include "BaseEntity.h"
class Platform : public BaseEntity
{
public:
    Platform(sfPos pos = { 50 , 50 }, b2World* world = nullptr, sf::Vector2f size = { 64, 32 });
    Platform(const std::vector<sf::Vector2f>& points, b2World* world); // 
    ~Platform() override = default;

protected:
    void initBox2d(sfPos pos, sf::Vector2f size);
    void initChainShapeBox2d(const std::vector<sf::Vector2f>& points); //
};
