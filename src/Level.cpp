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
	//m_entities.push_back(Factory<BaseEntity>::instance().create(ObjectType::ForkSMURF, {5,5}, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::TripleGift, sfPos{500,200}, m_world));
	m_map_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MAP));
	//m_entities.emplace_back(EnemyFactory::instance().create(ObjectType::ForkSMURF, { 500,300 }, m_world, m_player));
	//m_entities.emplace_back(EnemyFactory::instance().create(ObjectType::BossSmurf, { 500,300 }, m_world, m_player));
	//m_entities.emplace_back(EnemyFactory::instance().create(ObjectType::PresentSmurf, { 500,400 }, m_world, m_player));
	//m_entities.emplace_back(EnemyFactory::instance().create(ObjectType::RegularSmurf, { 500,400 }, m_world, m_player));
	//m_entities.push_back(Factory<BaseEntity>::instance().create(ObjectType::SMURF, {5,5}, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::SingleGift, sfPos{300,200}, m_world));
	m_entities.push_back(Factory::instance().create(ObjectType::TripleGift, sfPos{400,200}, m_world));
	loadStaticPlatformsFromJson("newww_map.tmj");
	m_map_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MAP));
	//m_entities.emplace_back(EnemyFactory::instance().create(ObjectType::SMURF, { 500,300 }, m_world, m_player));

}


void Level::update(float deltaTime)
{	
	removeMarkedEntities();

	m_player->update(deltaTime);

	for (auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void Level::draw(sf::RenderWindow& window)
{
	window.draw(m_map_sprite);
	for (auto& entity : m_entities)
	{
		//m_floor.draw(window);
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
                    // 💡 זיהוי פלטפורמה משופרת מבוססת polyline
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

                    std::cout << " ImprovPlatform created with " << vertices.size() << " points\n";
                    m_entities.push_back(std::move(platform));
                }
                else {
                    // 📦 פלטפורמה מלבנית רגילה
                    float x = obj["x"];
                    float y = obj["y"];
                    float width = obj["width"];
                    float height = obj["height"];

                    sfPos center{ x + width / 2.f, y + height / 2.f };
                    sf::Vector2f size{ width, height };

                    auto platform = std::make_unique<Platform>(center, m_world, size);

                    std::cout << " Platform created at: (" << center.x << ", " << center.y
                        << ") size: " << size.x << "x" << size.y << '\n';

                    m_entities.push_back(std::move(platform));
                }
            }
        }
    }
}


void Level::removeMarkedEntities() {
	for (auto it = m_entities.begin(); it != m_entities.end(); ) {
		if ((*it)->shouldBeRemoved()) {
			it = m_entities.erase(it);
		}
		else {
			++it;
		}
	}
}

const sf::Sprite& Level::getBackground() const {
	return m_map_sprite;
}