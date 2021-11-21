#pragma once
#include "Enemy.h"
#include "Player.h"
#include "AssetStore.h"
#include "CircleBulletPattern.h"

const int DamagePerBullet = 1;
const int ScreenHeight = 810;
const int ScreenWidth = 1080;

Enemy::Enemy(float x, float y) {
	this->currentBulletPattern = new CircleBulletPattern();
	this->position = { x, y };
	this->currentFrame = 0;
	this->framesFromStart = 0;
}

void Enemy::update(Player *player) {
	this->updateBullets(player);
}

void Enemy::updateBullets(Player *player) {
	this->currentFrame++;
	this->updateBulletPosition();
	this->createBulletIfNeeded();
	this->checkBulletCollisions(player);
}

void Enemy::updateBulletPosition() {
	// Only keep bullets that are inside bounds
	std::vector<GameStatus::BulletInfo> aux;
	for (int i = 0; i < GameStatus::getInstance().getEnemyBulletsNumber(); ++i) {
		GameStatus::BulletInfo bullet = GameStatus::getInstance().getEnemyBullet(i);
		bullet.position = { bullet.position.x + bullet.speed.x, bullet.position.y + bullet.speed.y };
		if ((bullet.position.x > 0 && bullet.position.x < ScreenWidth)
			&& ((bullet.position.y > 0 && bullet.position.y < ScreenHeight))) {
			aux.push_back(bullet);
		}
	}
	this->bulletPositions = aux;
}

void Enemy::createBulletIfNeeded() {
	if (this->currentFrame % this->currentBulletPattern->getFramesBetweenWaves() == 0) {
		this->currentBulletPattern->createBullet(this->currentFrame, this->position, &this->bulletPositions);
	}
}

void Enemy::checkBulletCollisions(Player *player) {
	std::vector<GameStatus::BulletInfo> aux;
	for (int i = 0; i < this->bulletPositions.size(); ++i) {
		GameStatus::BulletInfo current = this->bulletPositions[i];
		this->bulletPositions[i].position = {
			current.position.x + current.speed.x,
			current.position.y + current.speed.y
		};
		if (!player->checkCollision(this->bulletPositions[i].position)) {
			aux.push_back(this->bulletPositions[i]);
		}
		else {
			player->setLife(player->getLife() - DamagePerBullet);
		}
	}
	this->bulletPositions = aux;
}

Vector2 Enemy::getPosition() {
	return this->position;
}


std::vector<GameStatus::BulletInfo> Enemy::getBulletPositions() {
	return this->bulletPositions;
}

Enemy::~Enemy() {
	delete this->currentBulletPattern;
}