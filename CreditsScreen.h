#pragma once
#include "Screen.h"

class CreditsScreen : public Screen {
public:
    CreditsScreen(int width, int height);
    void updateGameStatus();
    void draw();
};