#pragma once
#include "BaseScreen.h"
#include <memory>
#include "Player.h"
#include "Level.h"
#include "cube.h"
#include <vector>
#include <ContactListener.h>

class GamePlay : public BaseScreen {
public:
	using BaseScreen::BaseScreen;
	GamePlay(sf::RenderWindow* window);//TODO: load things
	~GamePlay() override = default;
	void update(float deltaTime) override;
	void draw() override;
	void handleInput(const sf::Event& event, float deltaTime) override;
	sf::Vector2f getMouseWorldPosition();
	void addEntity(std::unique_ptr<BaseEntity> entity);
private:
	std::unique_ptr<b2World> m_world;
	std::unique_ptr<Player> m_player;
	Level m_level;
	std::vector<Cube> m_cubes;
	sf::RenderWindow* m_window = nullptr;

	void drawUI();
	void centerCameraOnPlayer();
	std::unique_ptr<ContactListener> m_contactListener;
};