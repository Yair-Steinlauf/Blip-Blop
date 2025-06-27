#include "SingleShotGiftStrategy.h"
#include "GiftRegistrar.h"
#include "Movment/GunMovment/SingleShotStrategy.h"
#include "Player.h"

static GiftRegistrar<
    ObjectType::SingleGift,
    SingleShotGiftStrategy,
    Direction::Right
> reg;

void SingleShotGiftStrategy::applyEffect(Player& player) {
    DataLoader::getInstance().getSound(ObjectType::machineGunWord).play();
    player.setGun(std::make_unique<SingleShotStrategy>(), AnimationSet::Blip, SINGLE_SHOOT_TIME, DataLoader::getInstance().getSound(ObjectType::shotGunSound));
}
