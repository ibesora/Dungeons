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
    void drawText();
    const char *getTextFromId(int id);

    int textAnimFrame;
    int timesAtTheBeginning;
    float textAlpha;
    bool showingText;
    Rectangle currentFrameRec;
};