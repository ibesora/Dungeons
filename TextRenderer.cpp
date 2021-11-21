#include "TextRenderer.h"
#include "AssetStore.h"
#include <string.h>

TextRenderer::TextRenderer() {
}

TextRenderer &TextRenderer::getInstance() {
    static TextRenderer instance;
    return instance;
}

void TextRenderer::draw(const char *text, int posX, int posY, int fontSize, Color color) {
    const int charWidth = 49;
    const int length = strlen(text);
    const float fontSizeY = 46.0f/49.0f * fontSize;
    for (int i = 0; i < length; ++i) {
        Rectangle srcRec = this->getCharacterMapping(text[i]);
        Vector2 position = {posX + i*fontSize, posY};
        Rectangle destRec = { (int)position.x, (int)position.y, fontSize, fontSizeY };
        Vector2 origin = { 0, 0 };
        Renderer::DrawTexturePro(AssetStore::getInstance().getFontTexture(), srcRec, destRec, origin, 0.0f, color);
    }
}

Rectangle TextRenderer::getCharacterMapping(const char character) {
    int base = 66; // ? symbol
    if (character >= 'A' && character <= 'Z') base = character - 65;
    else if (character >= 'a' && character <= 'z') base = character - 97 + 26;
    else if (character == ' ') base = 91;
    else if (character == '/') base = 79;
    else if (character == '-') base = 68;
    else if (character == '.') base = 62;
    else if (character == '(') base = 73;
    else if (character == ')') base = 74;
    else if (character == '!') base = 67;
    else if (character == '\'') base = 71;
    else if (character == ',') base = 63;

    const int charWidth = 49;
    const int charHeight = 46;
    const int columns = 10;
    const int row = base / columns;
    const int column = base % columns;
    return { column * charWidth, row * charHeight, charWidth, charHeight };
}