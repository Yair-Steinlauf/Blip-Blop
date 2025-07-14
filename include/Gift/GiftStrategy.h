
#pragma once
class Player;

class IEffectStrategy {
public:
    virtual ~IEffectStrategy() = default;
    virtual void applyEffect(Player& player) = 0;
};
