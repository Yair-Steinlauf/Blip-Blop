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

}


void Level::update(float deltaTime)
{	
	m_player->update(deltaTime);

	for (auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void Level::draw(sf::RenderWindow& window)
{
	for (auto& entity : m_entities)
	{
		//m_floor.draw(window);
		entity->draw(window);
	}
	m_player->draw(window);
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

				auto platform = std::make_unique<StaticEntity>(center, m_world, size);

				//  הוספת טקסטורה לציור (זמנית לצורך בדיקות)
				sf::Image debugImage;
				debugImage.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height), sf::Color::Red);

				sf::Texture debugTexture;
				debugTexture.loadFromImage(debugImage);

				//platform->initSprite(debugTexture);

				//  הדפסת בדיקה
				std::cout << " Platform created at: (" << center.x << ", " << center.y
					<< ") size: " << size.x << "x" << size.y << '\n';

				m_entities.push_back(std::move(platform));
			}
		}
	}
}


