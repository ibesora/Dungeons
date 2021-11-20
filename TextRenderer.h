#pragma once
#include "Renderer.h"

class TextRenderer {
public:
    TextRenderer(TextRenderer &other) = delete;
    void operator=(const TextRenderer &) = delete;
    static TextRenderer &getInstance();
    void draw(const char *text, int posX, int posY, int fontSize, Color color);

protected:
    TextRenderer();
    Rectangle getCharacterMapping(const char character);
};
