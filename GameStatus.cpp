#include "GameStatus.h"
#include "Screen.h"
#include "EndingScreen.h"
#include "WinScreen.h"
#include "Player.h"
#include "Enemy.h"
#include "AssetStore.h"
#include "Map.h"

GameStatus::GameStatus() {
    this->isPlaying = false;
    this->player = nullptr;
    this->enemy = nullptr;
    this->currentScreen = nullptr;
}

GameStatus &GameStatus::getInstance() {
    static GameStatus instance;
    return instance;
}

Player *GameStatus::getPlayer() {
    return this->player;
}

void GameStatus::setInitialScreen(Screen *initialScreen) {
    this->currentScreen = initialScreen;
    this->reset();
}

void GameStatus::reset() {
    delete this->player;
    delete this->enemy;

    this->isPlaying = this->currentScreen->getType() == ScreenType::Gameplay;
    Map::getInstance().reset();
    const Vector2 playerPosition = Map::getInstance().getPlayerStartingPosition();
    this->player = new Player(playerPosition.x, playerPosition.y);
    const Vector2 enemyPosition = Map::getInstance().getEnemyStartingPosition();
    this->enemy = new Enemy(enemyPosition.x, enemyPosition.y);
}

Screen *GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {

    if (this->isPlaying) {
        this->updatePlayer();
        this->updateEnemy();
        if (this->player->getLife() == 0) this->changeCurrentScreen(new EndingScreen(this->currentScreen->getWidth(), this->currentScreen->getHeight()));
    }

    this->getCurrentScreen()->updateGameStatus();
}

void GameStatus::updatePlayer() {
    this->player->update();
}

void GameStatus::updateEnemy() {
    if (Map::getInstance().areThereEnemies()) this->enemy->update(this->player);
}

void GameStatus::changeCurrentScreen(Screen *nextScreen) {
    // TODO: Do some kind of transition between screens?
    delete this->currentScreen;
    this->currentScreen = nextScreen;
    this->isPlaying = (this->currentScreen->getType() == ScreenType::Gameplay);
}

Vector2 GameStatus::getPlayerPosition() {
    return this->player->getPosition();
}

int GameStatus::getPlayerLife() { return this->player->getLife(); }

Music GameStatus::getCurrentSong() {
    if (this->currentScreen->getType() == ScreenType::Gameplay) return AssetStore::getInstance().getGameSong();
    else return AssetStore::getInstance().getMenuSong();
}

GameStatus::~GameStatus() {
    delete this->currentScreen;
    delete this->player;
}

int GameStatus::getEnemyBulletsNumber() { 
    if(Map::getInstance().areThereEnemies()) return (int)this->enemy->getBulletPositions().size();
    return 0;
}
GameStatus::BulletInfo GameStatus::getEnemyBullet(int index) { return this->enemy->getBulletPositions()[index]; }