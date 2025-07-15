#include "Level.h"
#include "Factory.h"
#include "BaseEnemy.h"
#include "Constance.h"
#include "../external/json.hpp"
#include <fstream>
#include"EnemyFactory.h"

Level::Level(Player* player , b2World* world)
	:m_player(player), m_world(world)
{
	m_map_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MAP));
	m_entities.push_back(Factory::instance().create(ObjectType::SingleGift, sfPos{7500,480}, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::TripleGift, sfPos{6000,500 }, m_world));

	m_entities.push_back(Factory::instance().create(ObjectType::LifeGift, sfPos{8000,500 }, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::LifeGift, sfPos{10000,500 }, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::LifeGift, sfPos{13000,500 }, m_world));
	loadStaticPlatformsFromJson("newww_map.tmj");
	m_map_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MAP));
}


void Level::update(float deltaTime)
{
    m_enemySpawnTimer += deltaTime;

    /* 1. הפעלת גל */
    if (m_waveNumber < static_cast<int>(WAVE_TABLE.size()) &&
        !m_isWaveActive &&
        m_player->getPosition().x >= WAVE_TABLE[m_waveNumber].triggerX)
    {
        spawnWave();
        m_isWaveActive = true;

        float left = WAVE_TABLE[m_waveNumber].triggerX;
        float right = left + WAVE_TABLE[m_waveNumber].zoneWidth;
        m_zoneLeft = left;
        m_zoneRight = right;
        m_player->setMovementBounds(left, right);
    }

    /* ▼ 1.5  – טִפְטוּף אויבים כל 0.5 ש׳ ---------------------- */
    if (m_isWaveActive && m_toSpawnStagger > 0)
    {
        m_staggerTimer += deltaTime;
        if (m_staggerTimer >= STAGGER_INTERVAL)
        {
            m_staggerTimer = 0.f;
            --m_toSpawnStagger;

            const auto& w = WAVE_TABLE[m_waveNumber];
            auto one = EnemyFactory::instance().createWave(
                1, m_world, m_player,
                w.triggerX,
                w.triggerX + w.zoneWidth);
            addEntity(std::move(one.front()));
        }
    }
    /* ---------------------------------------------------------- */

    /* 2. סיום גל */
    if (m_isWaveActive && BaseEnemy::getAliveCount() == 0 &&
        m_toSpawnStagger == 0)
    {
        m_isWaveActive = false;
        ++m_waveNumber;

        m_zoneLeft = -INFINITY;
        m_zoneRight = INFINITY;
        m_player->clearMovementBounds();
    }

    /* 3. ניקוי ועדכונים */
    removeMarkedEntities();

    m_player->update(deltaTime);
    for (auto& entity : m_entities)
        entity->update(deltaTime);
}


void Level::draw(sf::RenderWindow& window)
{
	window.draw(m_map_sprite);
	for (auto& entity : m_entities)
	{

		entity->draw(window);
	}
	m_player->draw(window);
}

void Level::addEntity(std::unique_ptr<BaseEntity> entity) {
	m_entities.push_back(std::move(entity));
}

void Level::loadStaticPlatformsFromJson(const std::string& path)
{
    using json = nlohmann::json;

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open: " + path);

    json mapData;
    file >> mapData;

    for (const auto& layer : mapData["layers"]) {
        if (layer["type"] == "objectgroup" && layer["name"] == "platform") {
            for (const auto& obj : layer["objects"]) {

                if (obj.contains("polyline")) {

                    const auto& points = obj["polyline"];
                    float baseX = obj["x"];
                    float baseY = obj["y"];

                    std::vector<sf::Vector2f> vertices;
                    for (const auto& p : points) {
                        float px = p["x"];
                        float py = p["y"];
                        vertices.emplace_back(baseX + px, baseY + py);
                    }

                    auto platform = std::make_unique<Platform>(vertices, m_world);

                    m_entities.push_back(std::move(platform));
                }
                else {

                    float x = obj["x"];
                    float y = obj["y"];
                    float width = obj["width"];
                    float height = obj["height"];

                    sfPos center{ x + width / 2.f, y + height / 2.f };
                    sf::Vector2f size{ width, height };

                    auto platform = std::make_unique<Platform>(center, m_world, size);

                        

                    m_entities.push_back(std::move(platform));
                }
            }
        }
    }
}


void Level::removeMarkedEntities()
{
    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [](auto& p) { return p->shouldBeRemoved(); }),
        m_entities.end());
}

const sf::Sprite& Level::getBackground() const {
	return m_map_sprite;
}

void Level::spawnWave()
{
    const auto& w = WAVE_TABLE[m_waveNumber];
    int total = w.enemyCount;

    int firstBatch = std::min(FIRST_BURST, total);
    m_toSpawnStagger = total - firstBatch;
    m_staggerTimer = 0.f;

    auto burst = EnemyFactory::instance().createWave(
        firstBatch, m_world, m_player,
        w.triggerX,
        w.triggerX + w.zoneWidth);

    for (auto& e : burst)
        addEntity(std::move(e));
}

