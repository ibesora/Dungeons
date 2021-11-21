#pragma once
#include "GameStatus.h"
#include <vector>

class BulletPattern;
class Player;

class Enemy {
public:
	Enemy(float x, float y);
	void update(Player *player);
	std::vector<GameStatus::BulletInfo> getBulletPositions();
	bool checkCollision(Vector2 point);
	Vector2 getPosition();
	~Enemy();
protected:
	void updateBulletPosition();
	void updateBullets(Player *player);
	void checkBulletCollisions(Player *player);
	void createBulletIfNeeded();

	BulletPattern *currentBulletPattern;
	Vector2 position;
	int currentFrame;
	int framesFromStart;
	std::vector<GameStatus::BulletInfo> bulletPositions;
};