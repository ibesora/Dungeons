#pragma once
#include "Renderer.h"
class Player;
class Screen;
class Music;

class GameStatus
{
public:
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
    ~GameStatus();
protected:
    GameStatus();
    void updatePlayer();
private:
    bool isPlaying;
    Player *player;
    Screen *currentScreen;
};

