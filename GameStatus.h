#pragma once
#include "Renderer.h"

class Player;
class Screen;
class Music;
class Enemy;

class GameStatus
{
public:
    struct BulletInfo {
        Vector2 speed;
        Vector2 position;
        BulletInfo(Vector2 speed, Vector2 position) : speed(speed), position(position) {}
    };
    static GameStatus &getInstance();
    Player *getPlayer();
    void setInitialScreen(Screen *initialScreen);
    Screen *getCurrentScreen();
    void changeCurrentScreen(Screen *nextScreen);
    Vector2 getPlayerPosition();
    int getPlayerLife();
    Music getCurrentSong();
    void reset();
    void update();
    int getEnemyBulletsNumber();
    BulletInfo getEnemyBullet(int index);
    ~GameStatus();
protected:
    GameStatus();
    void updatePlayer();
    void updateEnemy();
private:
    bool isPlaying;
    Player *player;
    Enemy *enemy;
    Screen *currentScreen;
};

