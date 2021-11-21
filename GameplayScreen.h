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
    void updateText();
    void drawBackground();
    void drawPlayer();
    void drawBullets();
    void drawPlayerHealth();
    void drawText();
    const char *getTextFromId(int id);
    const char *getWTFTextFromId(int id);

    int textAnimFrame;
    int timesAtTheBeginning;
    int timesWTF;
    float textAlpha;
    bool showingText;
    bool showingWTFText;
    Rectangle currentFrameRec;
};