#include "SingleShotGiftStrategy.h"
#include "GiftRegistrar.h"
#include "Movment/GunMovment/SingleShotStrategy.h"
#include "Player.h"

static GiftRegistrar<
    ObjectType::SingleGift,
    SingleShotGiftStrategy,
    Direction::machineGunWord
> reg;

void SingleShotGiftStrategy::applyEffect(Player& player) {
    DataLoader::getInstance().getSound(ObjectType::machineGunWord).play();
    player.setGun(std::make_unique<SingleShotStrategy>(), AnimationSet::RifleGunChar, SINGLE_SHOOT_TIME, DataLoader::getInstance().getSound(ObjectType::DeafultWeaponSound));
}
