// SpeedGiftStrategy.h
#pragma once
#include "GiftStrategy.h"

class LifeGiftStrategy : public IEffectStrategy {
public:
    void applyEffect(Player& player) override;
};
