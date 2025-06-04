#pragma once
#include "BaseScreen.h"

class GamePlay : public BaseScreen {
public:
	GamePlay();
	~GamePlay() override = default;
	void run() override;
private:
	void update(float deltaTime);
	void draw();
	void handleEvents();

};