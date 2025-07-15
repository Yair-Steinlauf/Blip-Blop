#pragma once
#include <array>
#include <limits>
#include "Entitys/BaseEntity.h"
#include "Player.h"
#include "Platform.h"

struct WaveInfo {
	float triggerX;
	float zoneWidth;
	int   enemyCount;
};

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
	void spawnWave();

	std::vector<std::unique_ptr<BaseEntity>> m_entities;
	Player* m_player;
	b2World* m_world;
	sf::Sprite m_map_sprite;
	float m_enemySpawnTimer = 0.f;
	const float m_enemySpawnInterval = 3.f;


	bool  m_isWaveActive = false;
	int   m_waveNumber = 0;
	float m_waveTimer = 0.f;
	const float m_waveInterval = 4.f;


	int   m_targetKills = 0;


	static constexpr std::array<WaveInfo, 3> WAVE_TABLE{ {
		{  1800.f,  6300.f,  30 },
		{ 8000.f,  6000.f,  70 },
		{ 13250.f,  1500, 50 }
	} };

	float m_gameProgress = 0.f;

	float m_zoneLeft = -std::numeric_limits<float>::infinity();
	float m_zoneRight = std::numeric_limits<float>::infinity();

	float m_staggerTimer = 0.f;
	int   m_toSpawnStagger = 0;
	static constexpr float STAGGER_INTERVAL = 0.5f;
	static constexpr int   FIRST_BURST = 10;

};