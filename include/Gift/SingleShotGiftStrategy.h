#pragma once
#include "GiftStrategy.h"
#include <memory>

class SingleShotGiftStrategy : public IEffectStrategy {
public:
    void applyEffect(Player& player) override;
};
