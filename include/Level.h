#pragma once
#include "Entitys/BaseEntity.h"
#include "Player.h"
#include "Platform.h"
class Level {
public:
	Level(Player* player, b2World* world = nullptr);
	~Level() = default;
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void addEntity(std::unique_ptr<BaseEntity> entity);
	void removeMarkedEntities();
private:
	void loadStaticPlatformsFromJson(const std::string& path);
	std::vector<std::unique_ptr<BaseEntity>> m_entities;
	Player* m_player;
	b2World* m_world;
	sf::Sprite m_map_sprite;
};