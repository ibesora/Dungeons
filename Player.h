#pragma once
#include "Renderer.h"
#include "GameStatus.h"

const int PlayerWidthInPx = 8;
const int PlayerHeightInPx = 8;

class Player {
public:
	Player(float x, float y);
	Vector2 getPosition();
	int getLife();
	void setLife(int life) { this->life = life; }
	void setGodMode(bool godModeActive);
	void update();
	void draw();
	bool checkCollision(Vector2 point);
protected:
	void updatePlayer();
	void updatePosition(float x, float y);

	Vector2 position;
	int life;
	bool godMode;
};