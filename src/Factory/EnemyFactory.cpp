#include "EnemyFactory.h"
#include "BaseEntity.h"
#include <cstdlib>   
#include <ctime>     
#include "Player.h"
EnemyFactory& EnemyFactory::instance()
{
	static auto instance = EnemyFactory();
	return instance;
}

bool EnemyFactory::registerType(ObjectType t, FuncType f)
{
	m_map.emplace(t, f);
	return true;
}

std::unique_ptr<BaseEntity> EnemyFactory::create(ObjectType t, sfPos pos, b2World* world, Player* player) const
{
	auto object = m_map.find(t);
	if (object == m_map.end())
		throw std::runtime_error("Cannot Find Current Object\n");
	return (object->second)(pos, world, player);
}



std::unique_ptr<BaseEntity>
EnemyFactory::createRandom(b2World* world,
    Player* player,
    sfPos    pos) const
{
    if (m_map.empty())
        throw std::runtime_error("EnemyFactory is empty");

    /* בחירת טיפוס אקראי: */
    static bool init = (std::srand((unsigned)std::time(nullptr)), true);
    int idx = std::rand() % m_map.size();
    auto it = std::next(m_map.begin(), idx);

    /* יצירה והחזרה */
    return create(it->first, pos, world, player);
}



std::vector<std::unique_ptr<BaseEntity>>
EnemyFactory::createWave(int count,
    b2World* world,
    Player* player,
    float zoneLeft,
    float zoneRight) const
{
    std::vector<std::unique_ptr<BaseEntity>> wave;
    wave.reserve(count);

    static constexpr float SPAWN_MARGIN = 100.f;          // לא צמוד לגבולות
    float groundY = player->getPosition().y -50.f;       // ≈ גובה הקרקע

    for (int i = 0; i < count; ++i)
    {
        float x = zoneLeft + SPAWN_MARGIN +
            static_cast<float>(std::rand()) / RAND_MAX *
            (zoneRight - zoneLeft - 2 * SPAWN_MARGIN);

        wave.push_back(createRandom(world, player, sfPos{ x-50, groundY }));
    }
    return wave;
}

