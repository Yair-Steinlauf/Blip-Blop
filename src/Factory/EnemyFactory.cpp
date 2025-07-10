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



std::unique_ptr<BaseEntity> EnemyFactory::createRandom(b2World* world, Player* player) const
{
    if (m_map.empty())
        throw std::runtime_error("EnemyFactory is empty");

    std::vector<ObjectType> keys;
    for (const auto& pair : m_map)
        keys.push_back(pair.first);

    static bool initialized = false;
    if (!initialized) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }

    int index = std::rand() % keys.size();
    ObjectType randomType = keys[index];

    sf::Vector2f playerPos = player->getPosition();

    constexpr float MIN_DIST_FROM_PLAYER = 150.f;
    constexpr float MAX_DIST_FROM_PLAYER = 800.f;

    float x = 0.f;
    do {
        x = playerPos.x - MAX_DIST_FROM_PLAYER + static_cast<float>(std::rand()) / RAND_MAX * (2 * MAX_DIST_FROM_PLAYER);
        // זה יגריל x בטווח [player_x - 800, player_x + 800]
    } while (std::abs(x - playerPos.x) < MIN_DIST_FROM_PLAYER);

    constexpr float GROUND_Y = 720.f; // החלף בהתאם למפה שלך
    sfPos pos(x, playerPos.y);

    return create(randomType, pos, world, player);
}



std::vector<std::unique_ptr<BaseEntity>> EnemyFactory::createWave(int count, b2World* world, Player* player) const
{
    std::vector<std::unique_ptr<BaseEntity>> wave;
    wave.reserve(count); // שיפור ביצועים – מקצה מראש

    for (int i = 0; i < count; ++i)
    {
        wave.push_back(createRandom(world, player));
    }

    return wave;
}