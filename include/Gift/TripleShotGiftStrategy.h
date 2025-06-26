#pragma once
#include "GiftStrategy.h"
#include <memory>

class TripleShotGiftStrategy : public IEffectStrategy {
public:
    void applyEffect(Player& player) override;
};
