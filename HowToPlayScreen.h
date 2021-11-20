#pragma once
#include "Screen.h"

class HowToPlayScreen : public Screen {
public:
    HowToPlayScreen(int width, int height);
    void updateGameStatus();
    void draw();
private:
};