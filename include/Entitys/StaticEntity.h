#pragma once
#include "BaseEntity.h"

class StaticEntity : public BaseEntity {
public:
    StaticEntity(sfPos pos = { 50,50 }, b2World* world = nullptr, sf::Vector2f size = { 64, 32 });
    ~StaticEntity() override = default;
    void initBox2d(sfPos pos, sf::Vector2f size);
};



