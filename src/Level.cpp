#include "Level.h"
#include "Factory.h"
#include "BaseEnemy.h"
#include "Constance.h"
#include "../external/json.hpp"
#include <fstream>

Level::Level(Player* player , b2World* world)
	:m_player(player), m_world(world)
{
	//m_entities.push_back(Factory<BaseEntity>::instance().create(ObjectType::SMURF, {5,5}, m_world));
	//m_entities.push_back(Factory::instance().create(ObjectType::FLOOR, sfPos{500,550/*0,SCREEN_HEIGHT - 20 */}, m_world));
	loadStaticPlatformsFromJson("newww_map.tmj");
	m_map_sprite.setTexture(DataLoader::getInstance().getP2Texture(ObjectType::MAP));

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
				float x = obj["x"];
				float y = obj["y"];
				float width = obj["width"];
				float height = obj["height"];

				sfPos center{ x + width / 2.f, y + height / 2.f };
				sf::Vector2f size{ width, height };

				auto platform = std::make_unique<Platform>(center, m_world, size);

				//  ����� ������� ����� (����� ����� ������)
				sf::Image debugImage;
				debugImage.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height), sf::Color::Red);

				sf::Texture debugTexture;
				debugTexture.loadFromImage(debugImage);

				//platform->initSprite(debugTexture);

				//  ����� �����
				std::cout << " Platform created at: (" << center.x << ", " << center.y
					<< ") size: " << size.x << "x" << size.y << '\n';

				m_entities.push_back(std::move(platform));
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
