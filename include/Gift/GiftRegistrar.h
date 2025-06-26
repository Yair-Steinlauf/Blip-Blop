#pragma once
#include "Factory.h"
#include "Gift.h"
#include "DataLoader.h"

/*
 * GiftRegistrar
 * -------------
 * Obj        – ערך enum מסוג ObjectType (למשל ObjectType::SingleTripleGift)
 * StrategyT  – מחלקת-אסטרטגיה (למשל SingleShotGiftStrategy)
 * Dir        – ערך enum מסוג Direction (ברירת-מחדל Right)
 *
 * עצם סטטי אחד יירשם אוטומטית בזמן טעינת התכנית ויאפשר
 *  Factory::create(...) לייצר את ה-Gift בלי קוד ידני נוסף.
 */
template<ObjectType Obj,
    typename   StrategyT,
    Direction  Dir = Direction::Right>
class GiftRegistrar
{
public:
    GiftRegistrar()
    {
        Factory::instance().registerType(
            Obj,
            [](sfPos pos, b2World* world) -> std::unique_ptr<BaseEntity>
            {
                return std::make_unique<Gift>(
                    &DataLoader::getInstance()
                    .getP2Texture(ObjectType::characterSprite),
                    pos,
                    world,
                    std::make_unique<StrategyT>(),
                    Dir
                );
            });
    }

private:
    /** מופע סטטי יחיד – הפעולה האמיתית מתבצעת בבנאי שלו */
    static GiftRegistrar<Obj, StrategyT, Dir> s_instance;
};

/* הגדרת המשתנה הסטטי (נדרשת לתבניות) */
template<ObjectType O, typename S, Direction D>
GiftRegistrar<O, S, D> GiftRegistrar<O, S, D>::s_instance;
