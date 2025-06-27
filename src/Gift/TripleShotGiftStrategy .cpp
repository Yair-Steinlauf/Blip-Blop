#include "TripleShotGiftStrategy.h"
#include "GiftRegistrar.h"
#include "Movment/GunMovment/TripleShotStrategy.h"
#include "Player.h"

static GiftRegistrar<
    ObjectType::TripleGift,
    TripleShotGiftStrategy,
    Direction::Left
> reg;

void TripleShotGiftStrategy::applyEffect(Player& player) {
    //DataLoader::getInstance().getSound(ObjectType::shotGunWord).play();
    player.setGun(std::make_unique<TripleShotStrategy>(), AnimationSet::Blip, TRIPLE_SHOOT_TIME, DataLoader::getInstance().getSound(ObjectType::shotGunSound));
}
