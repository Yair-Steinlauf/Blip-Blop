#pragma once
#include "BaseScreen.h"
#include <memory>
#include "Player.h"

class GamePlay : public BaseScreen {
public:
	using BaseScreen::BaseScreen;
	GamePlay(sf::RenderWindow* window);//TODO: load things
	~GamePlay() override = default;
	void update(float deltaTime) override;
	void draw() override;
	void handleInput(const sf::Event& event) override;
private:
	sf::Sprite m_background;
	std::unique_ptr<Player> m_player;
};