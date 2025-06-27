#include "LifeGiftStrategy.h"
#include "GiftRegistrar.h"
#include "Player.h"

// רישום המתנה: LifeGift
static GiftRegistrar<
    ObjectType::LifeGift,
    LifeGiftStrategy,
    Direction::Right
> reg;


void LifeGiftStrategy::applyEffect(Player& player) {
    //DataLoader::getInstance().getSound(ObjectType::shotGunWord).play();
    player.addLife(1);
}