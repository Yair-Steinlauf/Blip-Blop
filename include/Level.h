#pragma once
#include "Entitys/BaseEntity.h"
#include "Player.h"
class Level {
public:
	Level(Player* player, b2World* world = nullptr);
	~Level() = default;
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	std::vector<std::unique_ptr<BaseEntity>> m_entities;
	Player* m_player;
	b2World* m_world;

};