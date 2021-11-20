#include "Player.h"
#include "InputHandler.h"
#include "AssetStore.h"
#include <algorithm>
#include "Renderer.h"

const int XSpeed = 20;
const int YSpeed = 20;
const int StartingLife = 1000;
const int GodMode = false;

Player::Player(float x, float y) {
    this->position = { x, y };
    this->life = StartingLife;
    this->godMode = GodMode;
}

void Player::update() {
    this->updatePlayer();
}

void Player::updatePlayer() {
    Vector2 newPosition = this->position;
    if (InputHandler::getInstance().isKeyDown(GLFW_KEY_DOWN)) newPosition.y += 2;
    else if (InputHandler::getInstance().isKeyDown(GLFW_KEY_UP)) newPosition.y -= 2;

    if (InputHandler::getInstance().isKeyDown(GLFW_KEY_RIGHT)) newPosition.x += 2;
    else if (InputHandler::getInstance().isKeyDown(GLFW_KEY_LEFT)) newPosition.x -= 2;

    this->updatePosition(newPosition.x, newPosition.y);
}

void Player::updatePosition(float x, float y) {
    Tilemap *tilemap = AssetStore::getInstance().getTilemap();
    const Rectangle playerRect = { x, y, PlayerWidthInPx, PlayerHeightInPx };
    if (!tilemap->checkCollision(playerRect)) {
        this->position = { x, y };
    }
}

Vector2 Player::getPosition() { return this->position; }
int Player::getLife() { return this->life; }
void Player::setGodMode(bool godMode) { this->godMode = godMode; }

void Player::draw() {
    Renderer::DrawTexture(AssetStore::getInstance().getPlayerTexture(), this->position.x, this->position.y, WHITE);
}