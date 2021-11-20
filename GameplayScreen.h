#pragma once
#include "Renderer.h"
#include "Screen.h"
#include "GameStatus.h"
#include <vector>

class AssetStore;

class GameplayScreen : public Screen {
public:
    GameplayScreen(int width, int height);
    void updateGameStatus();
    void draw();

private:
    void updatePlayerTexture();
    void drawBackground();
    void drawPlayer();

    int textAnimFrame;
    Rectangle currentFrameRec;
};