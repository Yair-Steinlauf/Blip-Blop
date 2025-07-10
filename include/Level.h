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
	const sf::Sprite& getBackground() const;
private:
	void loadStaticPlatformsFromJson(const std::string& path);
	void removeMarkedEntities();
	std::vector<std::unique_ptr<BaseEntity>> m_entities;
	Player* m_player;
	b2World* m_world;
	sf::Sprite m_map_sprite;
	float m_enemySpawnTimer = 0.f;
	const float m_enemySpawnInterval = 3.f;
	// בחלק ה-private
	float m_waveTimer = 0.0f;
	float m_waveInterval = 5.0f;
	int m_waveNumber = 0;
	int m_waveType = 0;

	void spawnWave();
	int getEnemyCount();

};