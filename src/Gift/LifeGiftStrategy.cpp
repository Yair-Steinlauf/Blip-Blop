#include "LifeGiftStrategy.h"
#include "GiftRegistrar.h"
#include "Player.h"


static GiftRegistrar<
    ObjectType::LifeGift,
    LifeGiftStrategy,
    Direction::lifeWord
> reg;


void LifeGiftStrategy::applyEffect(Player& player) {

    player.addLife(1);
}