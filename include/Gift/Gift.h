// Gift.h
#pragma once
#include "BaseEntity.h"
#include "GiftStrategy.h"

class Gift : public BaseEntity {
public:
    Gift(sf::Texture* tex, sfPos pos, b2World* world, std::unique_ptr<IEffectStrategy> strategy, Direction direction);
    void onCollisionEnter(BaseEntity* other) override;

private:
    std::unique_ptr<IEffectStrategy> m_strategy;
};
