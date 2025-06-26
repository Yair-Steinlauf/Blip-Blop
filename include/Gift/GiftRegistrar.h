#pragma once
#include "Factory.h"
#include "Gift.h"
#include "DataLoader.h"

/*
 * GiftRegistrar
 * -------------
 * Obj        � ��� enum ���� ObjectType (���� ObjectType::SingleTripleGift)
 * StrategyT  � �����-�������� (���� SingleShotGiftStrategy)
 * Dir        � ��� enum ���� Direction (�����-���� Right)
 *
 * ��� ���� ��� ����� �������� ���� ����� ������ ������
 *  Factory::create(...) ����� �� �-Gift ��� ��� ���� ����.
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
    /** ���� ���� ���� � ������ ������� ������ ����� ��� */
    static GiftRegistrar<Obj, StrategyT, Dir> s_instance;
};

/* ����� ������ ����� (����� �������) */
template<ObjectType O, typename S, Direction D>
GiftRegistrar<O, S, D> GiftRegistrar<O, S, D>::s_instance;
