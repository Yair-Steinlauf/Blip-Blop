#pragma once
#include <array>          // ← חייב להיות כאן
#include <limits>         // ← בשביל numeric_limits
#include "Entitys/BaseEntity.h"
#include "Player.h"
#include "Platform.h"

struct WaveInfo {
	float triggerX;      // ברגע שה‑player.x ≥ triggerX – הגל מתחיל
	float zoneWidth;     // רוחב האזור שבו השחקן כלוא עד ניקוי הגל
	int   enemyCount;    // כמות אויבים
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
	// בחלק ה-private
	  // שליטה בגלים
	bool  m_isWaveActive = false;
	int   m_waveNumber = 0;      // 0‑based: 0,1,2
	float m_waveTimer = 0.f;    // מונה זמן בין גלים
	const float m_waveInterval = 4.f; // מרווח בין גלים (שניות)

	// כמה אויבים חייבים למות בגל הנוכחי
	int   m_targetKills = 0;

	// קבועי גלים: כמות אויבים לכל גל
	static constexpr std::array<WaveInfo, 3> WAVE_TABLE{ {
		{  1800.f,  6300.f,  0 },   // גל 1
		{ 8000.f,  6000.f,  0 },   // גל 2
		{ 13250.f,  1500, 2 }    // גל 3
	} };
	// חישוב התקדמות (כרגע לפי X)
	float m_gameProgress = 0.f;

	float m_zoneLeft = -std::numeric_limits<float>::infinity();
	float m_zoneRight = std::numeric_limits<float>::infinity();

};